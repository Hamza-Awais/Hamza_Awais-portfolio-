#include <iostream>
#include <fstream>

using namespace std;


class Logger {
public:
    static void log(const char* msg) {
        ofstream file("system_log.txt", ios::app);
        file << msg << endl;
        file.close();
    }
};

class Student {
private:
    int id;
    char name[50];

public:
    Student() {
        id = 0;
        name[0] = '\0';
    }

    Student(int studentId, const char* studentName) {
        id = studentId;
        int i = 0;
        while (studentName[i] != '\0' && i < 49) {
            name[i] = studentName[i];
            i++;
        }
        name[i] = '\0';
    }

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << "ID: " << s.id << " | Name: " << s.name;
        return out;
    }
};

class PerformanceRecord {
private:
    float Assignments;
    float quiz;
    float exam;
    float studyHours;

public:
    PerformanceRecord(float att = 0, float q = 0, float ex = 0, float study = 0) {
        Assignments = att;
        quiz = q;
        exam = ex;
        studyHours = study;
    }

    float* getNormalizedFeatures() const {
        float* features = new float[4];
        features[0] = Assignments / 100.0f;
        features[1] = quiz / 100.0f;
        features[2] = exam / 100.0f;
        features[3] = studyHours / 10.0f;
        return features;
    }

    float getAssignments() const { return Assignments; }
    float getQuiz() const { return quiz; }
    float getExam() const { return exam; }
    float getStudyHours() const { return studyHours; }
};

class PerformanceResult {
private:
    float score;
    char category[20];

public:
    PerformanceResult(float finalScore = 0, const char* cat = "Unknown") {
        score = finalScore;
        int i = 0;
        while (cat[i] != '\0' && i < 19) {
            category[i] = cat[i];
            i++;
        }
        category[i] = '\0';
    }

    friend ostream& operator<<(ostream& out, const PerformanceResult& r) {
        out << "Score: " << r.score << " | Category: " << r.category;
        return out;
    }

    float getScore() const { return score; }
    const char* getCategory() const { return category; }
};


class MLModel {
public:
    virtual void train() = 0;
    virtual float predict(float* features) = 0;
    virtual ~MLModel() {}
};


class LogisticRegression : public MLModel {
private:
    float weights[4];

public:
    LogisticRegression() {
        weights[0] = 0.25f;
        weights[1] = 0.25f;
        weights[2] = 0.35f;
        weights[3] = 0.15f;
    }

    void train() {
        Logger::log("Model trained with fixed weights.");
    }


    float sigmoid(float x) {
        if (x < -6) return 0;
        if (x > 6) return 1;
        return 0.5f + x / 4.0f; 
    }

    float predict(float* features) {
        float z = 0;
        for (int i = 0; i < 4; i++) z += weights[i] * features[i];
        return sigmoid(z);
    }
};


class DataSet {
private:
    Student* students;
    PerformanceRecord* records;
    int count;

public:
    DataSet(int c) {
        count = c;
        students = new Student[count];
        records = new PerformanceRecord[count];
    }

    void addStudent(int index, Student s, PerformanceRecord r) {
        students[index] = s;
        records[index] = r;
    }

    Student& getStudent(int index) { return students[index]; }
    PerformanceRecord& getRecord(int index) { return records[index]; }
    int getCount() const { return count; }

    ~DataSet() {
        delete[] students;
        delete[] records;
    }
};


class PerformanceEvaluator {
private:
    MLModel* model;

public:
    PerformanceEvaluator(MLModel* m) { model = m; }

    PerformanceResult evaluate(PerformanceRecord& record) {
        float* features = record.getNormalizedFeatures();
        float score = model->predict(features);
        delete[] features;

        if (score >= 0.70)
            return PerformanceResult(score, "Excellent");
        else if (score >= 0.66)
            return PerformanceResult(score, "Good");
        else if (score >= 0.61)
            return PerformanceResult(score, "Average");
        else
            return PerformanceResult(score, "Poor");
    }
};


class FileManager {
public:
    static void save(const Student& s, const PerformanceResult& r) {
        ofstream file("results.txt", ios::app);
        file << s << " | " << r << endl;
        file.close();
    }
};


class ReportGenerator {
public:
    static void generateReport(DataSet& dataset, PerformanceEvaluator& evaluator) {
        ofstream report("report.txt");
        if (!report.is_open()) return;

        report << "===== STUDENT PERFORMANCE REPORT =====\n\n";

        for (int i = 0; i < dataset.getCount(); i++) {
            Student s = dataset.getStudent(i);
            PerformanceRecord r = dataset.getRecord(i);
            PerformanceResult result = evaluator.evaluate(r);

            report << s << "\n";
            report << "Assignments: " << r.getAssignments()
                << " | Quiz: " << r.getQuiz()
                << " | Exam: " << r.getExam()
                << " | Study Hours: " << r.getStudyHours() << "\n";
            report << result << "\n";
            report << "-------------------------------------\n";
        }

        report.close();
        Logger::log("Report generated: report.txt");
    }
};


void getValidatedName(const char* msg, char* buffer) {
    bool firstAttempt = true;
    while (true) {
        cout << msg;
        if (firstAttempt) {
            cin.ignore(1000, '\n');
            firstAttempt = false;
        }
        cin.getline(buffer, 50);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        bool isValid = true;
        int i = 0;
        while (buffer[i] != '\0') {
            char c = buffer[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
                isValid = false;
                break;
            }
            i++;
        }

        if (isValid && i > 0) return;
        cout << "Invalid input! Name must contain only letters.\n";
    }
}

float getValidatedFloat(const char* msg, float min, float max) {
    float value;
    while (true) {
        cout << msg;
        cin >> value;

        if (!cin.fail() && value >= min && value <= max) return value;

        cout << "Invalid input! Try again.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

int getValidatedInt(const char* msg, int min, int max) {
    int value;
    while (true) {
        cout << msg;
        cin >> value;

        if (!cin.fail() && value >= min && value <= max) return value;

        cout << "Invalid input! Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}


int main() {
    cout << "===== Student Performance Evaluation System =====\n";

    int numStudents = getValidatedInt("Enter number of students (1-100): ", 1, 100);
    DataSet dataset(numStudents);

    for (int i = 0; i < numStudents; i++) {
        char name[50];

        int id = getValidatedInt("\nStudent ID: ", 1, 100000);
        getValidatedName("Student Name: ", name);

        float Assignments = getValidatedFloat("Assignments (0-100): ", 0, 100);
        float quiz = getValidatedFloat("Quiz Marks (0-100): ", 0, 100);
        float exam = getValidatedFloat("Mid Exam Marks (0-100): ", 0, 100);
        float study = getValidatedFloat("Study Hours (0-10): ", 0, 10);

        dataset.addStudent(i, Student(id, name), PerformanceRecord(Assignments, quiz, exam, study));
    }

    LogisticRegression model;
    model.train();
    PerformanceEvaluator evaluator(&model);

    for (int i = 0; i < numStudents; i++) {
        PerformanceResult result = evaluator.evaluate(dataset.getRecord(i));
        cout << dataset.getStudent(i) << endl;
        cout << result << endl;

        FileManager::save(dataset.getStudent(i), result);
    }

    ReportGenerator::generateReport(dataset, evaluator);

    cout << "\nResults saved correctly. Report generated: report.txt\n";
    Logger::log("Program finished successfully.");

    return 0;
}
