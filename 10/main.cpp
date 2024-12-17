#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

const char PATH_DELIMETR = '/';

class Error { 
  private:
	std::string message;

  public:
	Error(std::string message) : message(message) {}

	void Print() const { 
		std::cout << "ERROR: " << message << std::endl;
	}
};

class Node {
  protected:
   std::string name;
  public:
    Node(std::string name) : name(name) {}

    std::string GetName() const { return name; }

    void Rename(std::string newName) { name = newName; }
    virtual void Print() const = 0;
};

class Directory: public Node {
  private:
   std::vector<Node*> components;
   Directory *parentDir;

  public:
    Directory(std::string name, Directory *parentDir) : Node(name), parentDir(parentDir) {}
	

	void PrintComponents() {
		for (auto comp : components) {
			comp->Print();
		}

		if (components.empty()) {
			std::cout << "(empty)" << std::endl;
		}
	}

	void Print() const override {
		std::cout << "[DIR] " << name << "/" << std::endl;
	}

	void PrintWithLayers(int layer = 0) const {
		for(int i = 0; i < layer; ++i) std::cout << "  ";
		this->Print();
		for (auto comp : components) {
			if (typeid(*comp) == typeid(Directory)) {
				static_cast<Directory*>(comp)->PrintWithLayers(layer + 1);
			}
		}
	}

	void CreateComponent(Node *node) {
		components.push_back(node);
	}

	void RemoveAllComponents() {
		for(auto it = components.begin(); it != components.end(); ++it) {
			if(typeid(**it) == typeid(Directory)) { static_cast<Directory*>(*it)->RemoveAllComponents(); }
			delete *it;
		}
	}

	void RemoveComponent(const Node *object) {
		for (auto it = components.begin(); it != components.end(); ++it) {
			if (*it == object) {
				if(typeid(**it) == typeid(Directory)) { static_cast<Directory*>(*it)->RemoveAllComponents(); }
				components.erase(it);
				break;
			}
		}
	}

	Node *FindComponentByName(std::string name) {
		for (auto comp:components) {
			if (comp->GetName() == name) {
				return comp;
			}
		}
		return nullptr;
	}

	std::vector<Node*> FindComponentsBySearch(std::string search) {
		std::vector<Node*> found;

		std::string regexPattern = search;

		regexPattern = std::regex_replace(regexPattern, std::regex("\\*"), ".*"); 
		regexPattern = std::regex_replace(regexPattern, std::regex("\\?"), ".");
		regexPattern = std::regex_replace(regexPattern, std::regex("\\|"), "|");

		std::regex regex(regexPattern);

		for (const auto& comp : components) {
			std::string name = comp->GetName();
			if (std::regex_match(name, regex)) {
				found.push_back(comp);
			}
    	}
		return found;
	}

        int CountComponentsBySearchAndType(std::string search,
                                           std::string type);

        Directory* GetParentDir() { return parentDir;}
};

class File: public Node {
  private:
    std::string description;
    Directory *directory;

   public:
    File(std::string name, std::string description, Directory *dir) : Node(name), description(description), directory(directory) {}
	void Print() const override {
		std::cout << "[FILE] " << name << std::endl;
	}
};

int Directory::CountComponentsBySearchAndType(std::string search, std::string type) {
	int count = 0;
	std::vector<Node*> found = FindComponentsBySearch(search);

	if(type != "FILE" && type != "DIR") {
		return found.size();
	}

	for (const auto& comp : found) {
		if (type == "FILE" && typeid(*comp) == typeid(File)) {
			count++;
		} else if (type == "DIR" && typeid(*comp) == typeid(Directory)) {
			count++;
		}
	}
	return count;
}

class FilesTree {
  private:
   	Directory *rootDirectory;
   	Directory *currentDirectory;

	Directory *_findDirByName(std::string name) {
		Node * findedNode = currentDirectory->FindComponentByName(name);
		if (typeid(*findedNode) != typeid(Directory)) {
			return nullptr;
		}

		return static_cast<Directory*>(findedNode);
	}

	Directory *_findDirByName(std::string name, Directory *fromDir) {
		Node * findedNode = fromDir->FindComponentByName(name);
		if (typeid(*findedNode) != typeid(Directory)) {
			return nullptr;
		}

		return static_cast<Directory*>(findedNode);
	}

	Directory *_findDirByPath(std::string path) {
		std::istringstream stream(path);

		std::string subPath;

		Directory *tmpDir = currentDirectory;

		while (std::getline(stream, subPath, PATH_DELIMETR)) {
			if (subPath == "..") {
				tmpDir = tmpDir->GetParentDir();
			} else {
				tmpDir = _findDirByName(subPath, tmpDir);
			}
		}

		return tmpDir;
	}

  public:
    FilesTree() {
		Directory *rootDir = new Directory("ROOT DIRECTORY", nullptr);
		rootDirectory = rootDir;
		currentDirectory = rootDir;
	} 

	void ShowTree() {
		currentDirectory->PrintWithLayers();
	}

	void ChangeDirectory(std::string path) {
		try {
			Directory *dir = _findDirByPath(path);
			if(!dir) {
				throw Error("Directory with this name does not exist");
			}
			currentDirectory = dir;
		} catch(Error error) {
			error.Print();
		}
	}

	void MoveObject(std::string name, std::string toPath) {
		try {
			Node *object = currentDirectory->FindComponentByName(name);
			Directory *toDir = _findDirByPath(toPath);

			if(!object) {
				throw Error("Object with this name does not exist");
			}

			if (!toDir) {
				throw Error("Directory with this name does not exist");
			}

			toDir->CreateComponent(object);
			currentDirectory->RemoveComponent(object);
		} catch(Error error) {
			error.Print();
		}
	}

	void RenameComponent(std::string oldName, std::string newName) {
		try {
			Node *node = currentDirectory->FindComponentByName(oldName);
			if (!node) {
				throw Error("Object with this name does not exist");
			}
			node->Rename(newName);
		} catch(Error error) {
			error.Print();
		}
	}

	void RemoveComponent(std::string name) {
		try {
			Node *object = currentDirectory->FindComponentByName(name);
			if (!object) {
				throw Error("Object with this name does not exist");
			}
			currentDirectory->RemoveComponent(object);
		} catch(Error error) {
			error.Print();
		}
	}

	void Search(std::string search) {
		try {
			std::vector<Node*> found = currentDirectory->FindComponentsBySearch(search);
			for (const auto& comp : found) {
				comp->Print();
			}
		} catch(...) {
			Error("Search failed").Print();
		}
	}

	void CountBuTypeAndSearch(std::string search, std::string type) {
		try {
			size_t count = currentDirectory->CountComponentsBySearchAndType(search, type);
			std::cout << "Count: " << count << std::endl;
		} catch(...) {
			Error("Count failed").Print();
		}
	}

	void CreateDir(std::string name) {
		try {
			Directory *newDir = new Directory(name, currentDirectory);
			currentDirectory->CreateComponent(newDir);
		} catch(...) {
			Error("Create dir failed").Print();
		}
	}

	void CreateFile(std::string name, std ::string desc) {
		try {
			File *newFile = new File(name, desc, currentDirectory);
			currentDirectory->CreateComponent(newFile);
		} catch(...) {
			Error("Create file failed").Print();
		}
	}

	void PrintCurrentDir() {
		std::cout << "Current directory: " << currentDirectory->GetName() << std::endl;
		currentDirectory->PrintComponents();
	}
};


void PrintScenaries(FilesTree *filesTree) {
	std::string choice;
	std::cout << "\nSelect an action:\n";
	std::cout << "Print all files - ls\n";
	std::cout << "Show tree - show_tree\n";
	std::cout << "Create file - create_file\n";
	std::cout << "Create dir - mkdir\n";
	std::cout << "Go to dir - cd\n";
	std::cout << "Rename object - rename\n";
	std::cout << "Move object - mv\n";
	std::cout << "Search object - search\n";
	std::cout << "Count by type and search - count, types - (FILE, DIR, ANY)\n";
	std::cout << "exit - to exit\n";

    do {
        std::cout << ">> ";
        std::cin >> choice;

        if (choice == "show_tree") {
			filesTree->ShowTree();
        } else if (choice == "mkdir") {
			std::string dirName;
			std::string desc;
			std::cout << "Enter a new dir name: ";
			std::cin >> dirName;
			filesTree->CreateDir(dirName);
        } else if (choice == "create_file") {
			std::string fileName;
			std::string desc;
			std::cout << "Enter a new file name: ";
			std::cin >> fileName;
			std::cout << "Enter a new file description: ";
			std::cin >> desc;
			filesTree->CreateFile(fileName, desc);
        } else if (choice == "rm") {
			std::string objectName;
			std::cout << "Enter an object name: ";
			std::cin >> objectName;
			filesTree->RemoveComponent(objectName);
        } else if (choice == "ls") {
			filesTree->PrintCurrentDir();
		} else if (choice == "cd") {
			std::string dirName;
			std::cout << "Enter dir name: ";
			std::cin >> dirName;
			filesTree->ChangeDirectory(dirName);
		} else if(choice == "rename") {
			std::string oldName;
			std::cout << "Enter an object name: ";
			std::cin >> oldName;
			std::string newName;
			std::cout << "Enter a new object name: ";
			std::cin >> newName;
			filesTree->RenameComponent(oldName, newName);
		} else if(choice == "mv") {
			std::string oldName;
			std::cout << "Enter an object name: ";
			std::cin >> oldName;
			std::string toPath;
			std::cout << "Enter a new path: ";
			std::cin >> toPath;
			filesTree->MoveObject(oldName, toPath);
		} else if(choice == "search") {
			std::string search;
			std::cout << "Enter a search string: ";
			std::cin >> search;
			filesTree->Search(search);
		} else if(choice == "count") {
			std::string search;
			std::string type;
			std::cout << "Enter a search string: ";
			std::cin >> search;
			std::cout << "Enter a type: ";
			std::cin >> type;
			filesTree->CountBuTypeAndSearch(search, type);
		}
    } while(choice != "exit");
}


int main() {
	FilesTree filesSystem;

	filesSystem.CreateDir("1");
	filesSystem.CreateDir("2");
	PrintScenaries(&filesSystem);

	return 0; 
}