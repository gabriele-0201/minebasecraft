#ifndef THREADSAFAMAP_H
#define THREADSAFAMAP_H

class RWL {
    private:
       std::atomic_int readRequests{0};
       std::atomic_int writeRequests{0};
       // this is like a listener for all the threads that modify a variable
       std::condition_variable cv;
       std::mutex mRead;
       std::mutex mWrite;

    public:
        inline void lockRead() {
            readRequests++;
            if(writeRequests > 0) {
                readRequests--;
                std::unique_lock<std::mutex> lock(mRead);
                readRequests++;
                lock.unlock();
            }
        }

        inline void unlockRead() {
            readRequests--;
        }

        inline void lockWrite() {
            mWrite.lock();
            writeRequests++;
            while(readRequests > 0) std::this_thread::yield();
        }

        inline void unlockWrite() {
            writeRequests--;
            mWrite.unlock();
        }
};

template <class Key, class Value, 
class Compare = std::less<Key>, 
class Alloc = std::allocator<std::pair<const Key, Value>>>
class ThreadSafeMap: public std::map<Key, Value, Compare, Alloc> {

    private:
        RWL _lock;
    public: 

    //ThreadSafeMap<Key, Value, Compare, Alloc>& operator=(const ThreadSafeMap<Key, Value, Compare, Alloc>& m) {
    typename::std::map<Key, Value, Compare, Alloc> operator=(const ThreadSafeMap<Key, Value, Compare, Alloc>& m) {
        _lock.lockWrite();
        auto res = std::map<Key, Value, Compare, Alloc>::operator=(m);
        _lock.unlockWrite();
        return res;
    }

    size_t size() noexcept {
        _lock.lockRead();
        auto res = std::map<Key, Value, Compare, Alloc>::size();
        _lock.unlockRead();
        return res;
    }

    // maybe [] operator

    typename::ThreadSafeMap<Key, Value, Compare, Alloc>::iterator insert(const typename std::map<Key, Value, Compare, Alloc>::value_type& v) {
        _lock.lockWrite();
        auto res = std::map<Key, Value, Compare, Alloc>::insert(v);
        _lock.unlockWrite();
        return res.first;
    }

    //typename::ThreadSafeMap<Key, Value, Compare, Alloc>::iterator erase(const Key& v) {
    size_t erase(const Key& v) {
        _lock.lockWrite();
        auto res = std::map<Key, Value, Compare, Alloc>::erase(v);
        _lock.unlockWrite();
        return res;
    }

    typename::ThreadSafeMap<Key, Value, Compare, Alloc>::iterator find(const Key& v) {
        _lock.lockRead();
        auto res = std::map<Key, Value, Compare, Alloc>::find(v);
        _lock.unlockRead();
        return res;
    }

    typename::ThreadSafeMap<Key, Value, Compare, Alloc>::iterator begin() {
        _lock.lockRead();
        auto res = std::map<Key, Value, Compare, Alloc>::begin();
        _lock.unlockRead();
        return res;
    }

    typename::ThreadSafeMap<Key, Value, Compare, Alloc>::iterator end() {
        _lock.lockRead();
        auto res = std::map<Key, Value, Compare, Alloc>::end();
        _lock.unlockRead();
        return res;
    }
};

#endif