#ifndef ACTIONPOOL_H
#define ACTIONPOOL_H

// #include <unordered_map>
// #include <QString>
// #include <memory>
// #include <queue>

// class BaseAction {
// public:
//     virtual ~BaseAction() = default;
//     virtual void Execute() = 0;
// };

// class ActionPool
// {
// public:
//     static ActionPool& GetInstance() {
//         static ActionPool instance;
//         return instance;
//     }

//     ~ActionPool(){}

//     template <typename T, typename... Args>
//     std::unique_ptr<T> GetAction(Args&&... args) {
//         QString type = typeid(T).name();
//         if (!pool[type].empty()) {
//             auto action = std::move(pool[type].front());
//             pool[type].pop();
//             T* casted = dynamic_cast<T*>(action.get());
//             if (casted) {
//                 casted->Set(std::forward<Args>(args)...);
//                 return std::unique_ptr<T>(static_cast<T*>(action.release()));
//             }
//         }
//         return std::make_unique<T>();
//     }

//     template <typename T>
//     void ReturnAction(std::unique_ptr<T> action) {
//         QString type = typeid(T).name();
//         pool[type].push(std::move(action));
//     }
// private:
//     std::unordered_map<QString, std::queue<std::unique_ptr<BaseAction>>> pool;
//     ActionPool() = default;
// };

#endif // ACTIONPOOL_H
