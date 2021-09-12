#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "TaskQueue.h"
#include "ThreadProcessor.h"

#define FILEPATH "..\\src.txt"
#define THREAD_COUNT 5

using namespace std;

vector<char> mergeArrays(vector<char> v1, vector<char> v2);
void readFile(string filePath, vector<char>& fileContent);
void writeFile(vector<char> charResult);
void SortChars(void* content);
TaskQueue* initQueue(int threadCount, vector<char> sortChars);

int main()
{
    vector<char> fileContent;
    readFile(FILEPATH, fileContent);
    TaskQueue *tqueue = initQueue(THREAD_COUNT, fileContent);

    ThreadProcessor tproc(tqueue);
    vector<void*> procResults = tproc.ExecuteQueue(THREAD_COUNT);
    
    if (procResults.size() == 0)
    {
        return 0;
    }

    vector<char> result(((vector<char>*)procResults[0])->begin(), ((vector<char>*)procResults[0])->end());
    for (int i = 1; i < procResults.size(); i++)
    {
        result = mergeArrays(result, *((vector<char>*)procResults[i]));
    }

    writeFile(result);
}

void writeFile(vector<char> charResult)
{
    std::ofstream file("../output.txt");
    for (char el : charResult) {
        file << el;
    }
}

void readFile(string filePath, vector<char>& fileContent)
{
    ifstream src(filePath);
    char el;

    while (src.get(el))
    {
        fileContent.push_back(el);
    }
}

void SortChars(void *content)
{
    vector<char>* obj = (vector<char>*)content;
    sort(obj->begin(), obj->end());
}

TaskQueue* initQueue(int threadCount, vector<char> sortChars)
{
    TaskQueue *tqueue = new TaskQueue();
    int charsPerThread = ceil((double)sortChars.size() / threadCount);
    for (int i = 0; i < threadCount; i++)
    {
        vector<char>* slice = new vector<char>(sortChars.begin() + i * charsPerThread,
            sortChars.size() < (i + 1) * charsPerThread ?
            sortChars.end() : sortChars.begin() + (i + 1) * charsPerThread);
        Task *t = new Task(SortChars, (void*)slice);
        tqueue->Enqueue(t);
    }

    return tqueue;
}

vector<char> mergeArrays(vector<char> v1, vector<char> v2)
{
    int i = 0, j = 0;
    vector<char> res{};
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] < v2[j])
            res.push_back(v1[i++]);
        else
            res.push_back(v2[j++]);
    }
    while (i < v1.size())
        res.push_back(v1[i++]);
    while (j < v2.size())
        res.push_back(v2[j++]);
    return res;
}