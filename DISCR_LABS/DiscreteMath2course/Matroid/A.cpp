#include <iostream>

#include <vector>
#include <algorithm>
#include <set>

struct task {
    long long deadline;
    long long fine;

    task(long long int deadline, long long int fine) : deadline(deadline), fine(fine) {}
};

std::vector<task> tasks;

struct cmp {
    bool operator() (const int &a, const int &b) {
        return tasks[a].fine < tasks[b].fine;
    }
};

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        long long d, w;
        std::cin >> d >> w;
        tasks.emplace_back(d, w);
    }
    std::sort(tasks.begin(), tasks.end(), [](const task &a, const task &b) {
        return a.deadline < b.deadline;
    });

    auto debugTasks = tasks;
    long long minFine = 0;
    std::set<int, cmp> notOverdue;
    long long curTime = 1;
    for (int i = 0; i < n; ++i) {
        if (tasks[i].deadline == 0) {
            minFine += tasks[i].fine;
            continue;
        }
        notOverdue.emplace(i);
        if (tasks[i].deadline >= curTime) curTime++;
        else {
            minFine += tasks[*notOverdue.begin()].fine;
            notOverdue.erase(notOverdue.begin());
        }
    }
    std::cout << minFine;
    return 0;
}

