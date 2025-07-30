#include "dialogpool.h"

DialogPool::DialogPool() {}

DialogPool::~DialogPool() {
    releaseAllDialogs();
}

DialogPool& DialogPool::instance() {
    static DialogPool pool;
    return pool;
}

void DialogPool::releaseDialog(const QString& type) {
    if (pool.contains(type)) {
        pool[type]->hide();
    }
}

void DialogPool::releaseAllDialogs()
{
    for (auto dialog : pool) {
        delete dialog;
    }
    pool.clear();
}

