# Student Performance Evaluation System

| **Course** | Object Oriented Programming (OOP) |
| **Language** | C++ |
| **Type** | Console application |

A console program that takes each student's assignment, quiz and mid-exam marks plus study hours, feeds them through a simplified Logistic Regression model, and classifies the student as Excellent, Good, Average or Poor. Results are saved to files and a full report is generated.

## Features
- Enter any number of students (1-100) with ID, name and four academic inputs
- Every input is validated: numbers are range-checked and names accept letters and spaces only
- A Logistic Regression model (fixed weights + sigmoid) converts the normalized inputs into a score between 0 and 1
- The score is mapped to a category: Excellent, Good, Average or Poor
- Each evaluated student is appended to `results.txt`
- A formatted `report.txt` is rewritten on every run with all students and their results
- Every major step is appended to `system_log.txt` by the Logger

## How it works
- Each record is normalized into a 4-element feature vector: assignments/100, quiz/100, exam/100, studyHours/10.
- The model combines them with weights 0.25, 0.25, 0.35, 0.15 into a value `z`, then applies a clamped sigmoid to get the score.
- Thresholds: score >= 0.70 Excellent, >= 0.66 Good, >= 0.61 Average, otherwise Poor.
- `PerformanceEvaluator` holds the model through an `MLModel` base-class pointer, so `predict()` is resolved at run time (dynamic polymorphism).

## OOP concepts used
- **Abstraction:** `MLModel` is an abstract class with pure virtual `train()` and `predict()`
- **Inheritance:** `LogisticRegression` derives from `MLModel`
- **Polymorphism:** virtual functions and a virtual destructor resolve the call at run time
- **Encapsulation:** private data members with public getters
- **Operator overloading:** friend `operator<<` for `Student` and `PerformanceResult`
- **Dynamic memory:** feature vector and the `DataSet` object arrays are allocated with `new[]` and freed with `delete[]`
- **Static members:** `Logger::log`, `FileManager::save`, `ReportGenerator::generateReport`

## Files
- `student_performance_evaluation_system.cpp`: the source code
- `Student_Performance_Evaluation_System_Documentation.docx`: full project documentation (regenerated report)
- `Output_Screenshots.docx`: screenshots of sample program output
- `UML_Diagram.png`: UML class diagram of the ten classes

