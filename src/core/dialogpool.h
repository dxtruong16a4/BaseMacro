#ifndef DIALOGPOOL_H
#define DIALOGPOOL_H

#include "DialogBase.h"

class DialogPool {
public:
    static DialogPool& instance();

    template <typename T>
    T* acquireDialog(const QString& type) {
        if (!pool.contains(type)) {
            pool[type] = new T();
        }
        return qobject_cast<T*>(pool[type]);
    }

    void releaseDialog(const QString& type);
    void releaseAllDialogs();

    void showDialog(){
        for (auto id : pool){
            qDebug() << id;
        }
    }

private:
    QMap<QString, DialogBase*> pool;

    DialogPool();
    ~DialogPool();
};

#endif // DIALOGPOOL_H
