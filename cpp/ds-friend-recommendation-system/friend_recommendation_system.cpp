#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;


template <typename T>
class DynamicArray {
private:
    T*  data;
    int count;
    int capacity;

    void resize() {
        capacity    = capacity * 2;
        T* newData  = new T[capacity];
        for (int i = 0; i < count; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    DynamicArray(int initialCapacity = 8)
        : count(0), capacity(initialCapacity) {
        data = new T[capacity];
    }

    ~DynamicArray() { delete[] data; }

    DynamicArray(const DynamicArray& other) : count(other.count), capacity(other.capacity) {
        data = new T[capacity];
        for (int i = 0; i < count; i++)
            data[i] = other.data[i];
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data;
        count    = other.count;
        capacity = other.capacity;
        data     = new T[capacity];
        for (int i = 0; i < count; i++)
            data[i] = other.data[i];
        return *this;
    }

    void pushBack(const T& value) {
        if (count == capacity) resize();
        data[count++] = value;
    }

    T& operator[](int index)             { return data[index]; }
    const T& operator[](int index) const { return data[index]; }

    int  size()    const { return count; }
    bool isEmpty() const { return count == 0; }

    void clear() { count = 0; }

    template <typename Comparator>
    void sortDescending(Comparator comparator) {
        for (int i = 0; i < count - 1; i++) {
            int bestIdx = i;
            for (int j = i + 1; j < count; j++) {
                if (comparator(data[j], data[bestIdx]))
                    bestIdx = j;
            }
            if (bestIdx != i) {
                T tmp        = data[i];
                data[i]      = data[bestIdx];
                data[bestIdx]= tmp;
            }
        }
    }
};


template <typename T>
class LinkedList {
public:
    struct Node {
        T    data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

private:
    Node* head;
    int   count;

public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other) : head(nullptr), count(0) {
        Node* cur = other.head;
        while (cur) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;
        clear();
        Node* cur = other.head;
        while (cur) {
            pushBack(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    int  size()    const { return count; }
    bool isEmpty() const { return count == 0; }

    Node* getHead() const { return head; }

    void pushFront(const T& value) {
        Node* n  = new Node(value);
        n->next  = head;
        head     = n;
        count++;
    }

    void pushBack(const T& value) {
        Node* n = new Node(value);
        if (!head) { head = n; count++; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
        count++;
    }

    bool contains(const T& value) const {
        Node* cur = head;
        while (cur) {
            if (cur->data == value) return true;
            cur = cur->next;
        }
        return false;
    }

    Node* find(const T& value) const {
        Node* cur = head;
        while (cur) {
            if (cur->data == value) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    bool remove(const T& value) {
        if (!head) return false;

        if (head->data == value) {
            Node* del = head;
            head = head->next;
            delete del;
            count--;
            return true;
        }

        Node* prev = head;
        Node* cur  = head->next;
        while (cur) {
            if (cur->data == value) {
                prev->next = cur->next;
                delete cur;
                count--;
                return true;
            }
            prev = cur;
            cur  = cur->next;
        }
        return false;
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head  = nullptr;
        count = 0;
    }

    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

template <typename T>
class Queue {
private:
    T*   data;
    int  frontIdx;
    int  backIdx;
    int  count;
    int  capacity;

    void resize() {
        int   newCap  = capacity * 2;
        T*    newData = new T[newCap];

        for (int i = 0; i < count; i++) {
            newData[i] = data[(frontIdx + i) % capacity];
        }

        delete[] data;
        data     = newData;
        frontIdx = 0;
        backIdx  = count;
        capacity = newCap;
    }

public:
    Queue(int initialCapacity = 16)
        : frontIdx(0), backIdx(0), count(0), capacity(initialCapacity) {
        data = new T[capacity];
    }

    ~Queue() { delete[] data; }

    Queue(const Queue&)            = delete;
    Queue& operator=(const Queue&) = delete;

    bool isEmpty() const { return count == 0; }
    int  size()    const { return count; }

    void enqueue(const T& value) {
        if (count == capacity) resize();
        data[backIdx] = value;
        backIdx       = (backIdx + 1) % capacity;
        count++;
    }

    void dequeue() {
        if (isEmpty()) return;
        frontIdx = (frontIdx + 1) % capacity;
        count--;
    }

    T& front() {
        return data[frontIdx];
    }

    const T& front() const {
        return data[frontIdx];
    }
};


template <typename K, typename V>
class HashMap {
public:
    struct KeyValue {
        K key;
        V value;
        KeyValue() {}
        KeyValue(const K& k, const V& v) : key(k), value(v) {}

        bool operator==(const KeyValue& other) const { return key == other.key; }
    };

private:
    LinkedList<KeyValue>* buckets;
    int   bucketCount;
    int   itemCount;

    int hashKey(int key) const {
        unsigned int uk = (unsigned int)key;
        return (int)((uk * 2654435761u) % (unsigned int)bucketCount);
    }

    int hashKey(const string& key) const {
        unsigned long hash = 5381;
        for (char c : key)
            hash = ((hash << 5) + hash) + (unsigned char)c;
        return (int)(hash % (unsigned int)bucketCount);
    }

    template <typename AnyK>
    int hashKey(const AnyK& key) const {
        return 0;
    }

    void rehash() {
        int   oldCount   = bucketCount;
        bucketCount      = bucketCount * 2;
        LinkedList<KeyValue>* newBuckets = new LinkedList<KeyValue>[bucketCount];

        for (int i = 0; i < oldCount; i++) {
            typename LinkedList<KeyValue>::Node* cur = buckets[i].getHead();
            while (cur) {
                int idx = hashKey(cur->data.key);
                newBuckets[idx].pushBack(cur->data);
                cur = cur->next;
            }
        }

        delete[] buckets;
        buckets = newBuckets;
    }

public:
    HashMap(int initialBuckets = 16) : bucketCount(initialBuckets), itemCount(0) {
        buckets = new LinkedList<KeyValue>[bucketCount];
    }

    ~HashMap() { delete[] buckets; }

    HashMap(const HashMap& other) : bucketCount(other.bucketCount), itemCount(0) {
        buckets = new LinkedList<KeyValue>[bucketCount];
        for (int i = 0; i < bucketCount; i++)
            buckets[i] = other.buckets[i];
        itemCount = other.itemCount;
    }

    HashMap& operator=(const HashMap& other) {
        if (this == &other) return *this;
        delete[] buckets;
        bucketCount = other.bucketCount;
        itemCount   = 0;
        buckets     = new LinkedList<KeyValue>[bucketCount];
        for (int i = 0; i < bucketCount; i++)
            buckets[i] = other.buckets[i];
        itemCount = other.itemCount;
        return *this;
    }

    void insert(const K& key, const V& value) {
        if (itemCount > 0 && (float)itemCount / bucketCount >= 0.75f)
            rehash();

        int idx = hashKey(key);
        typename LinkedList<KeyValue>::Node* cur = buckets[idx].getHead();
        while (cur) {
            if (cur->data.key == key) {
                cur->data.value = value;
                return;
            }
            cur = cur->next;
        }

        buckets[idx].pushBack(KeyValue(key, value));
        itemCount++;
    }

    V* get(const K& key) {
        int idx = hashKey(key);
        typename LinkedList<KeyValue>::Node* cur = buckets[idx].getHead();
        while (cur) {
            if (cur->data.key == key) return &cur->data.value;
            cur = cur->next;
        }
        return nullptr;
    }

    const V* get(const K& key) const {
        int idx = hashKey(key);
        typename LinkedList<KeyValue>::Node* cur = buckets[idx].getHead();
        while (cur) {
            if (cur->data.key == key) return &cur->data.value;
            cur = cur->next;
        }
        return nullptr;
    }

    bool contains(const K& key) const {
        return get(key) != nullptr;
    }

    V& operator[](const K& key) {
        if (!contains(key)) insert(key, V());
        return *get(key);
    }

    bool remove(const K& key) {
        int idx = hashKey(key);
        typename LinkedList<KeyValue>::Node* cur = buckets[idx].getHead();
        while (cur) {
            if (cur->data.key == key) {
                buckets[idx].remove(cur->data);
                itemCount--;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    int  size()    const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }

    void getAllEntries(KeyValue** out, int& outCount) const {
        outCount = 0;
        for (int i = 0; i < bucketCount; i++) {
            typename LinkedList<KeyValue>::Node* cur = buckets[i].getHead();
            while (cur) {
                out[outCount++] = &cur->data;
                cur = cur->next;
            }
        }
    }

    int getBucketCount() const { return bucketCount; }

    LinkedList<KeyValue>* getBuckets() const { return buckets; }
};


class User {
public:
    int id;
    string name;
    vector<string> interests;

    User() : id(0), name("") {}

    User(int id, string name, vector<string> interests)
        : id(id), name(name), interests(interests) {}

    unordered_set<string> interestSet() const {
        return unordered_set<string>(interests.begin(), interests.end());
    }

    void display() const {
        cout << "+----------------------------------+\n";
        cout << "| " << left << setw(32) << ("User ID: " + to_string(id)) << " |\n";
        cout << "| " << left << setw(32) << ("Name   : " + name) << " |\n";

        string text = "Interests: ";
        for (int i = 0; i < (int)interests.size(); i++) {
            text += interests[i];
            if (i + 1 < (int)interests.size()) text += ", ";
        }

        cout << "| " << left << setw(32) << text << " |\n";
        cout << "+----------------------------------+\n";
    }
};


struct BFSEntry {
    int userId;
    int distance;

    BFSEntry() : userId(-1), distance(0) {}
    BFSEntry(int userId, int distance) : userId(userId), distance(distance) {}
};

struct NodeDepth {
    int nodeId;
    int depth;

    NodeDepth() : nodeId(0), depth(0) {}
    NodeDepth(int nodeId, int depth) : nodeId(nodeId), depth(depth) {}
};

class Graph {
private:
    HashMap<int, LinkedList<int>> adjList;

public:
    void addUser(int id) {
        if (!adjList.contains(id)) adjList.insert(id, LinkedList<int>());
    }

    void addFriend(int u, int v) {
        addUser(u);
        addUser(v);

        LinkedList<int>* first = adjList.get(u);
        LinkedList<int>* second = adjList.get(v);

        if (!first->contains(v)) first->pushBack(v);
        if (!second->contains(u)) second->pushBack(u);
    }

    void removeFriend(int u, int v) {
        LinkedList<int>* first = adjList.get(u);
        LinkedList<int>* second = adjList.get(v);

        if (first) first->remove(v);
        if (second) second->remove(u);
    }

    bool areFriends(int u, int v) const {
        const LinkedList<int>* list = adjList.get(u);
        return list && list->contains(v);
    }

    LinkedList<int> getFriends(int id) const {
        const LinkedList<int>* list = adjList.get(id);
        if (!list) return LinkedList<int>();
        return *list;
    }

    DynamicArray<BFSEntry> bfs(int startId, int maxDepth) const {
        DynamicArray<BFSEntry> result;
        if (!adjList.contains(startId)) return result;

        HashMap<int, bool> visited;
        Queue<NodeDepth> pending;

        visited.insert(startId, true);
        pending.enqueue(NodeDepth(startId, 0));

        while (!pending.isEmpty()) {
            NodeDepth current = pending.front();
            pending.dequeue();

            if (current.depth >= maxDepth) continue;

            const LinkedList<int>* neighbours = adjList.get(current.nodeId);
            if (!neighbours) continue;

            LinkedList<int>::Node* node = neighbours->getHead();
            while (node) {
                if (!visited.contains(node->data)) {
                    int distance = current.depth + 1;
                    visited.insert(node->data, true);
                    result.pushBack(BFSEntry(node->data, distance));
                    pending.enqueue(NodeDepth(node->data, distance));
                }
                node = node->next;
            }
        }

        return result;
    }

    int countMutualFriends(int u, int v) const {
        const LinkedList<int>* first = adjList.get(u);
        const LinkedList<int>* second = adjList.get(v);
        if (!first || !second) return 0;

        HashMap<int, bool> firstSet;
        LinkedList<int>::Node* node = first->getHead();
        while (node) {
            firstSet.insert(node->data, true);
            node = node->next;
        }

        int count = 0;
        node = second->getHead();
        while (node) {
            if (firstSet.contains(node->data)) count++;
            node = node->next;
        }

        return count;
    }

    const HashMap<int, LinkedList<int>>& getAdjList() const {
        return adjList;
    }

    int userCount() const {
        return adjList.size();
    }
};


struct Recommendation {
    int userId;
    int mutualFriends;
    int sharedInterests;
    double interestSimilarity;
    int distance;
    double score;

    Recommendation()
        : userId(-1), mutualFriends(0), sharedInterests(0),
          interestSimilarity(0), distance(0), score(0) {}
};

struct UserProfile {
    int id;
    DynamicArray<string> interests;

    UserProfile() : id(-1) {}
    UserProfile(int id) : id(id) {}
};

class RecommendationEngine {
public:
    DynamicArray<Recommendation> generateRecommendations(
        int targetId,
        const Graph& graph,
        const HashMap<int, UserProfile>& profiles,
        int topK = 5
    ) const {
        DynamicArray<Recommendation> recommendations;
        DynamicArray<BFSEntry> candidates = graph.bfs(targetId, 3);

        HashMap<int, bool> excluded;
        excluded.insert(targetId, true);

        LinkedList<int> currentFriends = graph.getFriends(targetId);
        LinkedList<int>::Node* node = currentFriends.getHead();
        while (node) {
            excluded.insert(node->data, true);
            node = node->next;
        }

        for (int i = 0; i < candidates.size(); i++) {
            int candidateId = candidates[i].userId;
            int distance = candidates[i].distance;

            if (excluded.contains(candidateId) || !profiles.contains(candidateId)) continue;

            const UserProfile* target = profiles.get(targetId);
            const UserProfile* candidate = profiles.get(candidateId);
            if (!target || !candidate) continue;

            Recommendation item;
            item.userId = candidateId;
            item.distance = distance;
            item.mutualFriends = graph.countMutualFriends(targetId, candidateId);
            item.sharedInterests = countSharedInterests(*target, *candidate);
            item.interestSimilarity = calculateInterestSimilarity(*target, *candidate);
            item.score = calculateScore(targetId, candidateId, distance, graph, profiles);
            recommendations.pushBack(item);
        }

        rankRecommendations(recommendations);

        DynamicArray<Recommendation> top;
        int limit = topK < recommendations.size() ? topK : recommendations.size();
        for (int i = 0; i < limit; i++) top.pushBack(recommendations[i]);
        return top;
    }

    double calculateScore(
        int targetId,
        int candidateId,
        int distance,
        const Graph& graph,
        const HashMap<int, UserProfile>& profiles
    ) const {
        double score = graph.countMutualFriends(targetId, candidateId) * 10.0;

        const UserProfile* target = profiles.get(targetId);
        const UserProfile* candidate = profiles.get(candidateId);

        if (target && candidate) {
            score += countSharedInterests(*target, *candidate) * 7.0;
            score += calculateInterestSimilarity(*target, *candidate) * 20.0;
        }

        if (distance == 2) score += 15.0;
        else if (distance == 3) score += 8.0;

        return score;
    }

    int countSharedInterests(const UserProfile& first, const UserProfile& second) const {
        HashMap<string, bool> set;
        for (int i = 0; i < first.interests.size(); i++) set.insert(first.interests[i], true);

        int count = 0;
        for (int i = 0; i < second.interests.size(); i++) {
            if (set.contains(second.interests[i])) count++;
        }
        return count;
    }

    double calculateInterestSimilarity(const UserProfile& first, const UserProfile& second) const {
        int shared = countSharedInterests(first, second);
        int total = first.interests.size() + second.interests.size() - shared;
        if (total == 0) return 0;
        return (double)shared / total;
    }

    void rankRecommendations(DynamicArray<Recommendation>& recommendations) const {
        recommendations.sortDescending([](const Recommendation& first, const Recommendation& second) {
            return first.score > second.score;
        });
    }
};


class FileManager {
private:
    vector<string> parseInterests(const string& line) {
        vector<string> interests;
        stringstream stream(line);
        string interest;

        while (getline(stream, interest, ',')) {
            while (!interest.empty() && interest.front() == ' ') interest.erase(interest.begin());
            while (!interest.empty() && interest.back() == ' ') interest.pop_back();
            if (!interest.empty()) interests.push_back(interest);
        }

        return interests;
    }

public:
    unordered_map<int, User> loadUsers(const string& filename) {
        unordered_map<int, User> users;
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Could not open " << filename << "\n";
            return users;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream stream(line);
            string idText;
            string name;
            string interestText;

            getline(stream, idText, ',');
            getline(stream, name, ',');
            getline(stream, interestText);

            try {
                int id = stoi(idText);
                users[id] = User(id, name, parseInterests(interestText));
            } catch (...) {
                cerr << "Invalid user record: " << line << "\n";
            }
        }

        return users;
    }

    vector<pair<int, int>> loadFriendships(const string& filename) {
        vector<pair<int, int>> friendships;
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Could not open " << filename << "\n";
            return friendships;
        }

        int first;
        int second;
        while (file >> first >> second) friendships.push_back({first, second});
        return friendships;
    }

    void saveUsers(const unordered_map<int, User>& users, const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not write to " << filename << "\n";
            return;
        }

        vector<int> ids;
        for (const auto& item : users) ids.push_back(item.first);
        sort(ids.begin(), ids.end());

        for (int id : ids) {
            const User& user = users.at(id);
            file << user.id << "," << user.name;
            for (const string& interest : user.interests) file << "," << interest;
            file << "\n";
        }
    }

    void saveFriendships(const unordered_map<int, vector<int>>& adjList, const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not write to " << filename << "\n";
            return;
        }

        set<pair<int, int>> friendships;
        for (const auto& item : adjList) {
            for (int friendId : item.second) {
                int first = min(item.first, friendId);
                int second = max(item.first, friendId);
                friendships.insert({first, second});
            }
        }

        for (const auto& friendship : friendships) {
            file << friendship.first << " " << friendship.second << "\n";
        }
    }
};


void printDivider(char character, int width) {
    for (int i = 0; i < width; i++) cout << character;
    cout << "\n";
}

void printUserCard(const User& user) {
    user.display();
}

void printRecommendationTable(const vector<Recommendation>& recommendations,
                              const unordered_map<int, User>& users) {
    if (recommendations.empty()) {
        cout << "No recommendations found.\n";
        return;
    }

    printDivider('=', 70);
    cout << left
         << setw(6) << "Rank"
         << setw(24) << "User"
         << setw(10) << "Score"
         << setw(10) << "Mutuals"
         << setw(10) << "Shared"
         << setw(10) << "Distance" << "\n";
    printDivider('-', 70);

    for (int i = 0; i < (int)recommendations.size(); i++) {
        const Recommendation& item = recommendations[i];
        string userName = "Unknown";
        auto user = users.find(item.userId);
        if (user != users.end()) {
            userName = user->second.name + " (ID:" + to_string(item.userId) + ")";
        }

        cout << left
             << setw(6) << i + 1
             << setw(24) << userName
             << setw(10) << fixed << setprecision(1) << item.score
             << setw(10) << item.mutualFriends
             << setw(10) << item.sharedInterests
             << setw(10) << item.distance << "\n";
    }

    printDivider('=', 70);
}

bool validateUserExists(int id, const unordered_map<int, User>& users) {
    if (users.find(id) == users.end()) {
        cout << "User ID not found.\n";
        return false;
    }
    return true;
}

string toLowerString(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char character) {
        return (char)tolower(character);
    });
    return text;
}

int getIntInput(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;
        cin >> value;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

void autoTest() {
    int passed = 0;
    int failed = 0;

    auto showResult = [&](const string& name, bool success) {
        cout << left << setw(42) << name << (success ? "PASS" : "FAIL") << "\n";
        if (success) passed++;
        else failed++;
    };

    FileManager manager;
    unordered_map<int, User> users = manager.loadUsers("users.txt");
    showResult("Load users", !users.empty());

    Graph graph;
    for (const auto& item : users) graph.addUser(item.first);

    vector<pair<int, int>> friendships = manager.loadFriendships("friends.txt");
    for (const auto& friendship : friendships) graph.addFriend(friendship.first, friendship.second);
    showResult("Load friendships", !friendships.empty());

    DynamicArray<BFSEntry> bfsResult = graph.bfs(1, 2);
    showResult("BFS depth 2", bfsResult.size() > 0);
    showResult("Mutual friends", graph.countMutualFriends(1, 6) >= 0);

    HashMap<int, UserProfile> profiles;
    for (const auto& item : users) {
        UserProfile profile(item.first);
        for (const string& interest : item.second.interests) profile.interests.pushBack(interest);
        profiles.insert(item.first, profile);
    }

    RecommendationEngine engine;
    DynamicArray<Recommendation> recommendations = engine.generateRecommendations(1, graph, profiles, 5);
    showResult("Recommendation limit", recommendations.size() <= 5);
    showResult("Recommendation score", recommendations.size() == 0 || recommendations[0].score >= 0);

    cout << "Passed: " << passed << "  Failed: " << failed << "\n";
}


class FriendRecommendationSystem {
private:
    unordered_map<int, User> users;
    Graph graph;
    RecommendationEngine engine;
    int nextId;

    HashMap<int, UserProfile> buildProfiles() const {
        HashMap<int, UserProfile> profiles;

        for (const auto& item : users) {
            const User& user = item.second;
            UserProfile profile(user.id);

            for (const string& interest : user.interests) {
                profile.interests.pushBack(interest);
            }

            profiles.insert(user.id, profile);
        }

        return profiles;
    }

    vector<string> splitInterests(const string& line) {
        vector<string> interests;
        string current;

        for (char character : line) {
            if (character == ',') {
                if (!current.empty()) interests.push_back(current);
                current.clear();
            } else {
                current += character;
            }
        }

        if (!current.empty()) interests.push_back(current);
        return interests;
    }

    void registerUser() {
        cout << "Enter name: ";
        string name;
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be blank.\n";
            return;
        }

        cout << "Enter interests separated by commas: ";
        string interestLine;
        getline(cin, interestLine);

        while (users.count(nextId)) nextId++;

        users[nextId] = User(nextId, name, splitInterests(interestLine));
        graph.addUser(nextId);
        cout << "User registered with ID: " << nextId << "\n";
        nextId++;
    }

    void addFriendMenu() {
        int first = getIntInput("Enter first user ID: ");
        if (!validateUserExists(first, users)) return;

        int second = getIntInput("Enter second user ID: ");
        if (!validateUserExists(second, users)) return;

        if (first == second) {
            cout << "Cannot friend yourself.\n";
            return;
        }

        if (graph.areFriends(first, second)) {
            cout << "Already friends.\n";
            return;
        }

        graph.addFriend(first, second);
        cout << users[first].name << " and " << users[second].name << " are now friends.\n";
    }

    void removeFriendMenu() {
        int first = getIntInput("Enter first user ID: ");
        if (!validateUserExists(first, users)) return;

        int second = getIntInput("Enter second user ID: ");
        if (!validateUserExists(second, users)) return;

        if (!graph.areFriends(first, second)) {
            cout << "These users are not friends.\n";
            return;
        }

        graph.removeFriend(first, second);
        cout << "Friendship removed.\n";
    }

    void viewFriends() {
        int id = getIntInput("Enter user ID: ");
        if (!validateUserExists(id, users)) return;

        LinkedList<int> friends = graph.getFriends(id);
        cout << "\nFriends of " << users[id].name << ":\n";
        printDivider('-', 35);

        if (friends.isEmpty()) {
            cout << "No friends yet.\n";
        } else {
            LinkedList<int>::Node* node = friends.getHead();
            while (node) {
                auto user = users.find(node->data);
                if (user != users.end()) cout << "[" << node->data << "] " << user->second.name << "\n";
                node = node->next;
            }
        }

        printDivider('-', 35);
    }

    void viewMutualFriends() {
        int first = getIntInput("Enter first user ID: ");
        if (!validateUserExists(first, users)) return;

        int second = getIntInput("Enter second user ID: ");
        if (!validateUserExists(second, users)) return;

        cout << "Mutual friends: " << graph.countMutualFriends(first, second) << "\n";
        LinkedList<int> firstFriends = graph.getFriends(first);
        LinkedList<int> secondFriends = graph.getFriends(second);

        LinkedList<int>::Node* firstNode = firstFriends.getHead();
        while (firstNode) {
            LinkedList<int>::Node* secondNode = secondFriends.getHead();
            while (secondNode) {
                if (firstNode->data == secondNode->data && users.count(firstNode->data)) {
                    cout << "[" << firstNode->data << "] " << users[firstNode->data].name << "\n";
                }
                secondNode = secondNode->next;
            }
            firstNode = firstNode->next;
        }
    }

    void displayRecommendations() {
        int id = getIntInput("Enter user ID: ");
        if (!validateUserExists(id, users)) return;

        int topK = getIntInput("How many recommendations: ");
        if (topK <= 0) topK = 5;

        HashMap<int, UserProfile> profiles = buildProfiles();
        DynamicArray<Recommendation> result = engine.generateRecommendations(id, graph, profiles, topK);
        vector<Recommendation> recommendations;

        for (int i = 0; i < result.size(); i++) recommendations.push_back(result[i]);

        cout << "\nTop recommendations for " << users[id].name << ":\n";
        printRecommendationTable(recommendations, users);
    }

    void searchUser() {
        cout << "Enter name to search: ";
        string query;
        getline(cin, query);
        query = toLowerString(query);

        bool found = false;
        for (const auto& item : users) {
            if (toLowerString(item.second.name).find(query) != string::npos) {
                cout << "[" << item.first << "] " << item.second.name << "\n";
                found = true;
            }
        }

        if (!found) cout << "No users found.\n";
    }

    void listAllUsers() {
        if (users.empty()) {
            cout << "No users registered.\n";
            return;
        }

        for (const auto& item : users) printUserCard(item.second);
    }

    void loadFromFiles() {
        FileManager manager;
        users = manager.loadUsers("users.txt");

        if (users.empty()) {
            cout << "No users were loaded.\n";
            return;
        }

        graph = Graph();
        nextId = 1;

        for (const auto& item : users) {
            graph.addUser(item.first);
            if (item.first >= nextId) nextId = item.first + 1;
        }

        vector<pair<int, int>> friendships = manager.loadFriendships("friends.txt");
        int loaded = 0;

        for (const auto& friendship : friendships) {
            if (users.count(friendship.first) && users.count(friendship.second)) {
                graph.addFriend(friendship.first, friendship.second);
                loaded++;
            }
        }

        cout << "Loaded " << users.size() << " users and " << loaded << " friendships.\n";
    }

    void saveToFiles() {
        FileManager manager;
        manager.saveUsers(users, "users.txt");

        const HashMap<int, LinkedList<int>>& source = graph.getAdjList();
        unordered_map<int, vector<int>> adjList;

        for (int i = 0; i < source.getBucketCount(); i++) {
            LinkedList<HashMap<int, LinkedList<int>>::KeyValue>::Node* item = source.getBuckets()[i].getHead();

            while (item) {
                int id = item->data.key;
                LinkedList<int>::Node* friendNode = item->data.value.getHead();

                while (friendNode) {
                    adjList[id].push_back(friendNode->data);
                    friendNode = friendNode->next;
                }

                item = item->next;
            }
        }

        manager.saveFriendships(adjList, "friends.txt");
        cout << "Data saved successfully.\n";
    }

public:
    FriendRecommendationSystem() : nextId(1) {}

    void showMenu() {
        cout << "\n";
        printDivider('=', 45);
        cout << "Friend Recommendation System\n";
        printDivider('=', 45);
        cout << "1. Load data from files\n";
        cout << "2. Register new user\n";
        cout << "3. Add friendship\n";
        cout << "4. Remove friendship\n";
        cout << "5. View all users\n";
        cout << "6. View user's friends\n";
        cout << "7. View mutual friends\n";
        cout << "8. Get friend recommendations\n";
        cout << "9. Search user by name\n";
        cout << "10. Save data to files\n";
        cout << "0. Exit\n";
        printDivider('=', 45);
    }

    void run() {
        cout << "Welcome to the Friend Recommendation System!\n";

        int choice = -1;
        while (choice != 0) {
            showMenu();
            choice = getIntInput("Enter choice: ");

            switch (choice) {
                case 1: loadFromFiles(); break;
                case 2: registerUser(); break;
                case 3: addFriendMenu(); break;
                case 4: removeFriendMenu(); break;
                case 5: listAllUsers(); break;
                case 6: viewFriends(); break;
                case 7: viewMutualFriends(); break;
                case 8: displayRecommendations(); break;
                case 9: searchUser(); break;
                case 10: saveToFiles(); break;
                case 0: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

int main() {
    FriendRecommendationSystem system;
    system.run();
    return 0;
}
