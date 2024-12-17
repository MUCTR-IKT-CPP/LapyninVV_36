template <typename T>
class CRUDRepository {
  private:
    std::vector<T*> items;
  public:
    CRUDRepository() {
        items = std::vector<T*>();
    }
    void Insert(T* item) { items.push_back(item); }
    T Get(int id) { return items; }
    void BulkInsert(std::vector<T*> newItems) { items.insert(items.end(), newItems.begin(), newItems.end()); }
    std::vector<T*> GetAll() { return items; }
};