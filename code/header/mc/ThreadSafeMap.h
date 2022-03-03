
template<class Key, class Value>
class ThreadSafeMap
{
    std::mutex m_;
    std::map<Key, Value> c_;

public:
    Value get(Key const& k) {
        std::unique_lock<decltype(m_)> lock(m_);
        return c_[k]; // Return a copy.
    }

    //void set(Key const& k, Value&& v) {
    void set(Key const& k, Value& v) {
        std::unique_lock<decltype(m_)> lock(m_);
        c_[k] = std::forward<Value>(v);
    }

    void insert(std::pair<Key const&, Value&&> entry) {
        std::unique_lock<decltype(m_)> lock(m_);
        //c_[entry.first] = std::forward<Value>(entry.second);
        c_.insert(std::make_pair(entry.first, std::forward<Value>(entry.second)));
    }

    //typename::std::map<Key, Value>::iterator find(std::pair<Key const&, Value&&> entry) {
    typename::std::map<Key, Value>::iterator find(Key const& key) {
        std::unique_lock<decltype(m_)> lock(m_);
        //c_[k] = std::forward<Value2>(v);
        return c_.find(key);
        //return c_.find(entry);
    }

    void erase(Key const& k) {
        std::unique_lock<decltype(m_)> lock(m_);
        c_.erase(k);
    }

    int size() {
        return c_.size();
    }

    typename::std::map<Key, Value>::iterator begin() {
        return c_.begin();
    }

    typename::std::map<Key, Value>::iterator end() {
        return c_.end();
    }

    // TODO assign operator and copy contructor
    ThreadSafeMap& operator= (const ThreadSafeMap& m) {
        c_ = m.c_;
        //m_ = m.m_.
        return *this;
    }
};