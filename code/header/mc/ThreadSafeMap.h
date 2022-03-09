#ifndef THREADSAFAMAP_H
#define THREADSAFAMAP_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <map>
#include <unordered_map>

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
//class Compare = std::less<Key>, 
class Hash = HashTuples::hash3tuple, 
class KeyEqual = std::equal_to<Key>,
//class Alloc = std::allocator<std::pair<const Key, Value>>>
class Alloc = std::allocator< std::pair<const Key, Value>>>
//class ThreadSafeMap: public std::map<Key, Value, Compare, Alloc> {
class ThreadSafeMap: public std::unordered_map<Key, Value, Hash, KeyEqual, Alloc> {

    private:
        RWL _lock;
    public: 

    //ThreadSafeMap<Key, Value, Compare, Alloc>& operator=(const ThreadSafeMap<Key, Value, Compare, Alloc>& m) {
    typename::std::unordered_map<Key, Value, Hash, KeyEqual, Alloc> operator=(const ThreadSafeMap<Key, Value, Hash, KeyEqual, Alloc>& m) {
        _lock.lockWrite();
        //auto res = std::map<Key, Value, Compare, Alloc>::operator=(m);
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::operator=(m);
        _lock.unlockWrite();
        return res;
    }

    size_t size() noexcept {
        _lock.lockRead();
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::size();
        //auto res = std::map<Key, Value, Compare, Alloc>::size();
        _lock.unlockRead();
        return res;
    }

    // maybe [] operator
    // typename::std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::mapped_type& operator[] ( const Key& k ){
    //     _lock.lockWrite();
    //     auto res = &std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::operator[](k);
    //     //auto res = std::map<Key, Value, Compare, Alloc>::insert(v);
    //     _lock.unlockWrite();
    //     return *res;
    // }

    void replace(const typename std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::value_type& v) {

        _lock.lockWrite();
        std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::operator[](v.first) = v.second;
        //auto res = std::map<Key, Value, Compare, Alloc>::insert(v);
        _lock.unlockWrite();
        //return *res;

    }

    typename::ThreadSafeMap<Key, Value, Hash, KeyEqual, Alloc>::iterator insert(const typename std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::value_type& v) {
        _lock.lockWrite();
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::insert(v);
        //auto res = std::map<Key, Value, Compare, Alloc>::insert(v);
        _lock.unlockWrite();
        return res.first;
    }

    typename::ThreadSafeMap<Key, Value, Hash, KeyEqual, Alloc>::iterator erase(const Key& v) {
    //size_t erase(const Key& v) {
        _lock.lockWrite();
        auto elem = find(v);
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::erase(elem);
        //auto res = std::map<Key, Value, Compare, Alloc>::erase(v);
        _lock.unlockWrite();
        return res;
    }

    typename::ThreadSafeMap<Key, Value, Hash, KeyEqual, Alloc>::iterator find(const Key& v) {
        _lock.lockRead();
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::find(v);
        //auto res = std::map<Key, Value, Compare, Alloc>::find(v);
        _lock.unlockRead();
        return res;
    }

    typename::ThreadSafeMap<Key, Value, Hash, KeyEqual, Alloc>::iterator begin() {
        _lock.lockRead();
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::begin();
        //auto res = std::map<Key, Value, Compare, Alloc>::begin();
        _lock.unlockRead();
        return res;
    }

    typename::ThreadSafeMap<Key, Value, Hash, KeyEqual, Alloc>::iterator end() {
        _lock.lockRead();
        auto res = std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>::end();
        //auto res = std::map<Key, Value, Compare, Alloc>::end();
        _lock.unlockRead();
        return res;
    }
};

#endif