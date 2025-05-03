#include "incidents.h"
#include "add_time.h"
#include "reduce_time.h"
#include "add_health.h"
#include "reduce_health.h"
#include <cstdlib>
#include <ctime>
#include <string>

// 声明外部变量
extern int DUEPosition;
extern HealthSystem playerHealth;  // 添加玩家血量系统

// 触发随机事件
IncidentType triggerRandomIncident(int& currentLevelTime, HealthSystem& playerHealth) {
    // 随机选择一个事件
    int eventCount = 6;  // 现在有6种事件
    int randomEvent = rand() % eventCount;
    
    IncidentType incident = static_cast<IncidentType>(randomEvent);
    
    // 根据事件类型执行相应操作
    switch(incident) {
        case REDUCE_TIME:
            reduceLevelTime(currentLevelTime);
            break;
        case PAUSE_DUE:
            pauseDUE();
            break;
        case REVERSE_DUE:
            reverseDUE(DUEPosition);
            break;
        case ADD_TIME:
            addLevelTime(currentLevelTime);
            break;
        case ADD_HEALTH:
            addHealth(playerHealth);
            break;
        case REDUCE_HEALTH:
            reduceHealth(playerHealth);
            break;
    }
    
    return incident;
}

#include <functional> // 添加函数指针支持

// 声明外部变量
extern int currentLevel;

// Define the function pointer type
using IncidentNameFunction = std::string(*)(IncidentType);

// Define the event name functions for each level
// APAI1001
std::string getIncidentNameLevel1(IncidentType incident) {
    switch (incident) {
        case REDUCE_TIME:
            return "Instantly understood KNN from Bilibili University [Reduce time by 5s]";
        case PAUSE_DUE:
            return "Collaborated smoothly with group [Pause due for 5s]";
        case REVERSE_DUE:
            return "Solved confusion by asking the prof [Reverse due by 3 spaces]";
        case ADD_TIME:
            return "Didn't understand the prof's PPT on probability [Add time by 10s]";
        case ADD_HEALTH:
            return "Discovered a relevant and easy-to-understand book [Add 1 health]";
        case REDUCE_HEALTH:
            return "Didn't understand tutorial due to lack of programming knowledge [Reduce health by 1]";
        default:
            return "Unknown incident";
    }
}

// COMP1117
std::string getIncidentNameLevel2(IncidentType incident) {
    switch (incident) {
        case REDUCE_TIME:
            return "Tutorial explained exercise in detail [Reduce time by 5s]";
        case PAUSE_DUE:
            return "Found midterm paper and cheated [Pause due for 5s]";
        case REVERSE_DUE:
            return "Pro helped debug in 10 minutes [Reverse due by 3 spaces]";
        case ADD_TIME:
            return "Struggled with testcase for two hours [Add time by 10s]";
        case ADD_HEALTH:
            return "Found great Python course on Bilibili [Add 1 health]";
        case REDUCE_HEALTH:
            return "Testcase wouldn't pass, debugged for two hours [Reduce health by 1]";
        default:
            return "Unknown incident";
    }
}

// CAES1000
std::string getIncidentNameLevel3(IncidentType incident) {
    switch (incident) {
        case REDUCE_TIME:
            return "Used GPT to complete a small section of an essay [Reduce time by 5s]";
        case PAUSE_DUE:
            return "Peer review provided constructive feedback [Pause due for 5s]";
        case REVERSE_DUE:
            return "Discussed with CSS Writing Center tutor [Reverse due by 3 spaces]";
        case ADD_TIME:
            return "Overslept morning class [Add time by 10s]";
        case ADD_HEALTH:
            return "Obtained several excellent sample essays from senior students [Add 1 health]";
        case REDUCE_HEALTH:
            return "Caught using GPT for assignment [Reduce health by 1]";
        default:
            return "Unknown incident";
    }
}

//STAT1016
std::string getIncidentNameLevel4(IncidentType incident) {
    switch (incident) {
        case REDUCE_TIME:
            return "Found complete database on Kaggle [Reduce time by 5s]";
        case PAUSE_DUE:
            return "Collaborated with pro on data processing model [Pause due for 5s]";
        case REVERSE_DUE:
            return "Learned linear regression in Eddy's office [Reverse due by 3 spaces]";
        case ADD_TIME:
            return "Caught writing other assignments in lecture [Add time by 10s]";
        case ADD_HEALTH:
            return "Learned Excel for linear regression [Add 1 health]";
        case REDUCE_HEALTH:
            return "Group project lacked control group, negated research [Reduce health by 1]";
        default:
            return "Unknown incident";
    }
}

// MATH2014
std::string getIncidentNameLevel5(IncidentType incident) {
    switch (incident) {
        case REDUCE_TIME:
            return "Content already learned in high school [Reduce time by 5s]";
        case PAUSE_DUE:
            return "Tutor outlined key points before exam [Pause due for 5s]";
        case REVERSE_DUE:
            return "Professor extended assignment deadline [Reverse due by 3 spaces]";
        case ADD_TIME:
            return "Professor forgot to record the class [Add time by 10s]";
        case ADD_HEALTH:
            return "Found great calculus course on Bilibili [Add 1 health]";
        case REDUCE_HEALTH:
            return "Get confused in the tutorial [Reduce health by 1]";
        default:
            return "Unknown incident";
    }
}

// STAT2601
std::string getIncidentNameLevel6(IncidentType incident) {
    switch (incident) {
        case REDUCE_TIME:
            return "Tutor taught class while Wat was in meeting [Reduce time by 5s]";
        case PAUSE_DUE:
            return "Wat explained assignment questions in class [Pause due for 5s]";
        case REVERSE_DUE:
            return "Actively answered questions in forum, impressed Wat [Reverse due by 3 spaces]";
        case ADD_TIME:
            return "Missed 10 minutes of important content due to early start [Add time by 10s]";
        case ADD_HEALTH:
            return "Wat impressed by forum activity [Add 1 health]";
        case REDUCE_HEALTH:
            return "Overslept morning class [Reduce health by 1]";
        default:
            return "Unknown incident";
    }
}

// Default
std::string getIncidentNameDefault([[maybe_unused]] IncidentType incident) {
    return "Unknown incident";
}

// Define an array of function pointers
IncidentNameFunction incidentNameFunctions[] = {
    getIncidentNameLevel1,
    getIncidentNameLevel2,
    getIncidentNameLevel3, 
    getIncidentNameLevel4,
    getIncidentNameLevel5,
    getIncidentNameLevel6,
    getIncidentNameDefault // Default function for levels beyond defined ones
};

// Updated getIncidentName function
std::string getIncidentName(IncidentType incident) {
    if (currentLevel >= 1 && currentLevel <= static_cast<int>(sizeof(incidentNameFunctions) / sizeof(incidentNameFunctions[0]))) {
        return incidentNameFunctions[currentLevel - 1](incident);
    }
    return incidentNameFunctions[sizeof(incidentNameFunctions) / sizeof(incidentNameFunctions[0]) - 1](incident);
}