# CV-Based Job Suitability and Domain Prediction System

| **Course** | Object Oriented Programming (OOP) |
| **Language** | C++ |
| **Type** | Console application (colored UI, Windows) |

A console program that reads a candidate's resume from a text file and predicts the most suitable IT domain for them. The prediction is made by a Random Forest of decision trees (skill, education and project) that each cast a vote, and the role with the majority of votes wins.

## Features
- Reads a resume file and parses `NAME`, `AGE`, `EDUCATION`, `SKILLS`, `PROJECTS` and `CERTIFICATIONS`
- Displays the candidate's full CV in a colored, formatted layout
- Predicts one of five outcomes: **Data Scientist**, **Web Developer**, **Game Developer**, **App Developer**, or **Versatile IT Specialist** (tie)
- Three independent decision trees vote on the result:
  - **Skill Tree** — scores skills by keyword and months of experience
  - **Education Tree** — scores the degree against each domain
  - **Project Tree** — scores project descriptions against each domain
- Majority vote decides the final role, with a confidence percentage
- Clean object-oriented design: inheritance, composition, abstract classes and dynamic polymorphism

## How it works
- Each tree returns one vote for the domain it thinks fits best.
- The three votes are tallied. The domain with the most votes wins; if two or more domains tie, the candidate is shown as a **Versatile IT Specialist** with every tied domain listed.
- Skill weight grows with experience: `weight = 2.0 + (months x 0.5)`.
- If no tree finds enough matching data, the result is **Insufficient Data**.

## OOP concepts used
- **Inheritance:** `Candidate` is a `Person`
- **Composition:** a `CV` holds `Skill`, `Project` and `Education` objects
- **Abstract class / pure virtual function:** `DecisionTree` with `vote()`
- **Dynamic polymorphism:** `RandomForest` calls `vote()` through base-class pointers
- **Dynamic memory:** every object and string is allocated with `new` and freed in destructors

## Resume file format
```
NAME: ...
AGE: ...
EDUCATION: ...
SKILLS: Name|Months, Name|Months
PROJECTS: Title|Description
CERTIFICATIONS: ...
```

## Files
- `cv_job_prediction_system.cpp`: the source code
- `CV_Job_Prediction_System_Documentation.docx`: full project documentation
- `Screen_shots_of_results.docx`: screenshots of sample program output

