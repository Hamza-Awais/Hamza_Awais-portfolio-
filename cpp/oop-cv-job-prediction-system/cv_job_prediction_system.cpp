#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;

void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void line(char ch, int n)
{
	for (int i = 0; i < n; i++) cout << ch;
	cout << endl;
}
void title(const char* t)
{
	setColor(11);
	line('=', 70);
	cout << "   " << t << endl;
	line('=', 70);
	setColor(7);
}
bool string_compare(const char* STRING1, const char* STRING2)
{
	if (STRING1 == nullptr || STRING2 == nullptr) return false;

	int i = 0;
	while (STRING1[i] != '\0' && STRING2[i] != '\0')
	{
		char char1 = STRING1[i];
		char char2 = STRING2[i];

		if (char1 >= 'A' && char1 <= 'Z')
			char1 = char1 + 32;
		if (char2 >= 'A' && char2 <= 'Z')
			char2 = char2 + 32;
		if (char1 != char2)
			return false;
		i++;
	}
	char final1 = STRING1[i];
	char final2 = STRING2[i];

	if (final1 >= 'A' && final1 <= 'Z') final1 = final1 + 32;
	if (final2 >= 'A' && final2 <= 'Z') final2 = final2 + 32;

	return (final1 == final2);
}
bool SEARCH_FOR_KEYWORD(const char* MAIN_STR, const char* SEARCH_WORD)
{
	if (MAIN_STR == nullptr || SEARCH_WORD == nullptr) return false;

	for (int i = 0; MAIN_STR[i] != '\0'; i++)
	{
		int j = 0;

		while (SEARCH_WORD[j] != '\0' && MAIN_STR[i + j] != '\0')
		{
			char main = MAIN_STR[i + j];
			char search = SEARCH_WORD[j];

			if (main >= 'A' && main <= 'Z')
				main = main + 32;

			if (search >= 'A' && search <= 'Z')
				search = search + 32;

			if (main != search)
				break;
			j++;
		}

		if (SEARCH_WORD[j] == '\0') return true;
	}
	return false;
}
static char* deep_copy(const char* source)
{
	if (source == nullptr)
		return nullptr;
	char* destination = new char[strlen(source) + 1];
	for (int i = 0; i <= strlen(source); i++)
		destination[i] = source[i];

	return destination;
}
void trim_spaces(char*& String)
{
	if (String == nullptr) return;
	while (String[0] == ' ' || String[0] == '\t' || String[0] == '\r' || String[0] == '\n')
		String++;
	int len = 0;
	while (String[len] != '\0')
		len++;
	while (len > 0 && (String[len - 1] == ' ' || String[len - 1] == '\t' ||
		String[len - 1] == '\r' || String[len - 1] == '\n'))
	{
		String[len - 1] = '\0';
		len--;
	}
}
class Skill {
private:
	char* skill_name;
	int months;
public:
	Skill(const char* name, int m) : months(m) { skill_name = deep_copy(name); }
	~Skill() { if (skill_name) delete[] skill_name; }


	const char* get_skill_name() const { return skill_name; }

	int get_months() const { return months; }
};
class Project {
private:
	char* title;
	char* description;
public:
	Project(const char* t, const char* d) 
	{
		title = deep_copy(t);
		description = deep_copy(d);
	}
	~Project() { delete[] title; delete[] description; }

	const char* get_title() const { return title; }

	const char* GET_DESC_RIPTION() const { return description; }
};
class Education
{
private:
	char* degree;
public:
	Education(const char* deg) { degree = deep_copy(deg); }
	~Education() { if (degree) delete[] degree; }
	const char* get_degree() const { return degree; }
	void display() const
	{
		if (degree) cout << "DEGREE: " << degree << endl;
	}
};
class CV
{
private:
	Skill* skills[15];
	Project* projects[15];
	Education* education;
	char* certifications;
	int skill_count;
	int project_count;

public:
	CV() : skill_count(0), project_count(0), certifications(nullptr), education(nullptr)
	{
		for (int i = 0; i < 15; i++)
		{
			skills[i] = nullptr;
			projects[i] = nullptr;
		}
	}

	~CV()
	{
		if (certifications) delete[] certifications;
		if (education) delete education;

		for (int i = 0; i < skill_count; i++)
		{
			if (skills[i]) delete skills[i];
		}

		for (int i = 0; i < project_count; i++)
		{
			if (projects[i]) delete projects[i];
		}
	}

	void set_education(const char* deg)
	{
		if (education) delete education;
		education = new Education(deg);
	}

	void add_skill(const char* s_name, int months)
	{
		if (skill_count < 15)
		{
			skills[skill_count] = new Skill(s_name, months);
			skill_count++;
		}
	}
	void add_project(const char* p_title, const char* p_desc)
	{
		if (project_count < 15) {
			projects[project_count] = new Project(p_title, p_desc);
			project_count++;
		}
	}
	void set_certifications(const char* certs)
	{
		if (certifications) delete[] certifications;
		certifications = deep_copy(certs);
	}
	int get_skill_count() const { return skill_count; }
	Skill* get_skill(int index) const { return skills[index]; }
	int get_project_count() const { return project_count; }
	Project* get_project(int index) const { return projects[index]; }
	const char* get_degree() const
	{
		return (education) ? education->get_degree() : "";
	}

	void display_cv() {
		if (education) {
			setColor(11);
			cout << "DEGREE: ";
			setColor(7);
			cout << education->get_degree() << endl;
		}
		cout << endl;
		setColor(14);
		line('-', 70);
		cout << "   SKILLS & EXPERTISE" << endl;
		line('-', 70);

		for (int i = 0; i < skill_count; i++)
		{
			setColor(10);
			cout << "  > ";
			setColor(7);
			cout << skills[i]->get_skill_name();

			setColor(8);
			cout << " [" << skills[i]->get_months() << " months]" << endl;
		}


		cout << endl;
		setColor(14);
		line('-', 70);
		cout << "   PROJECTS PORTFOLIO" << endl;
		line('-', 70);

		for (int i = 0; i < project_count; i++)
		{
			setColor(11);
			cout << "  [" << (i + 1) << "] " << projects[i]->get_title() << endl;

			setColor(7);

			cout << "      " << (char)192 << (char)196 << " Desc: " << projects[i]->GET_DESC_RIPTION() << endl;
		}

		if (certifications)
		{
			cout << endl;
			setColor(14);
			line('~', 70);
			setColor(11);
			cout << "CERTIFICATIONS: ";
			setColor(7);
			cout << certifications << endl;
			setColor(14);
			line('~', 70);
		}
		setColor(7);
	}
};
class Person
{
protected:
	char* name;
	int age;
public:
	Person() : name(nullptr), age(0) {}
	virtual ~Person() { if (name) delete[] name; }

	void set_name(const char* n)
	{
		if (name) delete[] name;
		name = deep_copy(n);
	}
	void set_age(int a) { age = a; }

	void display_person() const
	{
		setColor(11);
		cout << "NAME: ";

		setColor(7);
		if (name) cout << name << endl;
		else cout << "N/A" << endl;

		setColor(11);
		cout << "AGE:  ";

		setColor(7);
		cout << age << endl;
	}
};
class Candidate : public Person
{
private:
	CV* cv;
public:
	Candidate() { cv = new CV(); }
	~Candidate() { if (cv) delete cv; }
	CV* get_cv() { return cv; }
	void display_candidate()
	{
		display_person();
		if (cv)
		{
			cv->display_cv();
		}
		else
		{
			setColor(12);
			cout << "Error: No CV data found." << endl;
			setColor(7);
		}
	}
};
// abstract class
class DecisionTree
{
public:
	virtual const char* vote(Candidate* c) = 0;
};
class SkillTree : public DecisionTree
{
public:
	const char* vote(Candidate* c) override
	{
		CV* cv_ptr = c->get_cv();
		double ds_points = 0.0, web_points = 0.0, game_points = 0.0, app_points = 0.0;

		for (int i = 0; i < cv_ptr->get_skill_count(); i++)
		{
			Skill* sk = cv_ptr->get_skill(i);
			const char* s_name = sk->get_skill_name();
			int months = sk->get_months();
			double weight = 2.0 + (months * 0.5);

			if (SEARCH_FOR_KEYWORD(s_name, "Python") || SEARCH_FOR_KEYWORD(s_name, "SQL") || SEARCH_FOR_KEYWORD(s_name, "Machine") ||
				SEARCH_FOR_KEYWORD(s_name, "Pandas") || SEARCH_FOR_KEYWORD(s_name, "NumPy") || SEARCH_FOR_KEYWORD(s_name, "R-Language"))
				ds_points += weight;

			if (SEARCH_FOR_KEYWORD(s_name, "HTML") || SEARCH_FOR_KEYWORD(s_name, "CSS") || SEARCH_FOR_KEYWORD(s_name, "React") ||
				SEARCH_FOR_KEYWORD(s_name, "JavaScript") || SEARCH_FOR_KEYWORD(s_name, "Node") || SEARCH_FOR_KEYWORD(s_name, "Angular") ||
				SEARCH_FOR_KEYWORD(s_name, "Bootstrap"))
				web_points += weight;

			if (SEARCH_FOR_KEYWORD(s_name, "Unity") || SEARCH_FOR_KEYWORD(s_name, "C#") || SEARCH_FOR_KEYWORD(s_name, "Unreal") ||
				SEARCH_FOR_KEYWORD(s_name, "Engine") || SEARCH_FOR_KEYWORD(s_name, "DirectX") || SEARCH_FOR_KEYWORD(s_name, "OpenGL") ||
				SEARCH_FOR_KEYWORD(s_name, "C++"))
				game_points += weight;

			if (SEARCH_FOR_KEYWORD(s_name, "Flutter") || SEARCH_FOR_KEYWORD(s_name, "Java") || SEARCH_FOR_KEYWORD(s_name, "Swift") ||
				SEARCH_FOR_KEYWORD(s_name, "Kotlin") || SEARCH_FOR_KEYWORD(s_name, "Android") || SEARCH_FOR_KEYWORD(s_name, "iOS") ||
				SEARCH_FOR_KEYWORD(s_name, "Dart"))
				app_points += weight;
		}
		if (ds_points >= web_points && ds_points >= game_points && ds_points >= app_points && ds_points > 0) return "DATA SCIENTIST";
		if (web_points >= ds_points && web_points >= game_points && web_points >= app_points && web_points > 0) return "WEB DEVELOPER";
		if (game_points >= ds_points && game_points >= web_points && game_points >= app_points && game_points > 0) return "GAME DEVELOPER";
		if (app_points >= ds_points && app_points >= web_points && app_points >= game_points && app_points > 0) return "APP DEVELOPER";
		return "REJECTED";
	}
};
class EducationTree : public DecisionTree
{
public:
	const char* vote(Candidate* c) override
	{
		CV* cv_ptr = c->get_cv();
		const char* DEGREE = cv_ptr->get_degree();

		double ds_points = 0.0, web_points = 0.0, game_points = 0.0, app_points = 0.0;

		if (SEARCH_FOR_KEYWORD(DEGREE, "Data Science") || SEARCH_FOR_KEYWORD(DEGREE, "BSDS") ||
			SEARCH_FOR_KEYWORD(DEGREE, "Statistics") || SEARCH_FOR_KEYWORD(DEGREE, "Artificial Intelligence") ||
			SEARCH_FOR_KEYWORD(DEGREE, "BSAI"))
		{
			ds_points += 0.5;
		}
		else if (SEARCH_FOR_KEYWORD(DEGREE, "Computer Science") || SEARCH_FOR_KEYWORD(DEGREE, "BSCS") ||
			SEARCH_FOR_KEYWORD(DEGREE, "Computer Engineering") || SEARCH_FOR_KEYWORD(DEGREE, "BSCE"))
		{
			ds_points += 0.5;
			web_points += 0.5;
			game_points += 0.5;
			app_points += 0.5;
		}

		else if (SEARCH_FOR_KEYWORD(DEGREE, "Software Engineering") || SEARCH_FOR_KEYWORD(DEGREE, "BSSE") ||
			SEARCH_FOR_KEYWORD(DEGREE, "Information Technology") || SEARCH_FOR_KEYWORD(DEGREE, "BSIT") ||
			SEARCH_FOR_KEYWORD(DEGREE, "Cyber Security") || SEARCH_FOR_KEYWORD(DEGREE, "Information Systems"))
		{
			web_points += 0.5;
			game_points += 0.5;
			app_points += 0.5;
		}



		if (ds_points > 0 && ds_points == web_points && web_points == game_points)
			return "GENERAL IT";


		if (ds_points > web_points && ds_points > game_points && ds_points > app_points)
			return "DATA SCIENTIST";

		if (web_points > 0 && web_points == game_points)
			return "GENERAL IT";

		if (web_points > 0) return "WEB DEVELOPER";
		if (game_points > 0) return "GAME DEVELOPER";
		if (app_points > 0) return "APP DEVELOPER";

		return "NONE";
	}
};
class ProjectTree : public DecisionTree
{
public:
	const char* vote(Candidate* c) override
	{
		CV* cv_ptr = c->get_cv();
		double ds_pts = 0, web_pts = 0, game_pts = 0, app_pts = 0;

		for (int i = 0; i < cv_ptr->get_project_count(); i++)
		{

			ds_pts += 1.0;
			web_pts += 1.0;
			game_pts += 1.0;
			app_pts += 1.0;

			Project* pr = cv_ptr->get_project(i);
			const char* desc = pr->GET_DESC_RIPTION();

			if (SEARCH_FOR_KEYWORD(desc, "ML") || SEARCH_FOR_KEYWORD(desc, "Model") || SEARCH_FOR_KEYWORD(desc, "Data"))
				ds_pts += 1.5;
			if (SEARCH_FOR_KEYWORD(desc, "Frontend") || SEARCH_FOR_KEYWORD(desc, "UI") || SEARCH_FOR_KEYWORD(desc, "Website"))
				web_pts += 1.5;
			if (SEARCH_FOR_KEYWORD(desc, "Physics") || SEARCH_FOR_KEYWORD(desc, "Engine") || SEARCH_FOR_KEYWORD(desc, "Collision"))
				game_pts += 1.5;
			if (SEARCH_FOR_KEYWORD(desc, "Firebase") || SEARCH_FOR_KEYWORD(desc, "Mobile") || SEARCH_FOR_KEYWORD(desc, "Playstore"))
				app_pts += 1.5;
		}


		if (ds_pts >= web_pts && ds_pts >= game_pts && ds_pts >= app_pts && ds_pts > 0) return "DATA SCIENTIST";
		if (web_pts >= ds_pts && web_pts >= game_pts && web_pts >= app_pts && web_pts > 0) return "WEB DEVELOPER";
		if (game_pts >= ds_pts && game_pts >= web_pts && game_pts >= app_pts && game_pts > 0) return "GAME DEVELOPER";
		if (app_pts >= ds_pts && app_pts >= web_pts && app_pts >= game_pts && app_pts > 0) return "APP DEVELOPER";

		return "NONE";
	}
};
class RandomForest
{
private:
	DecisionTree* forest_trees[3];
public:
	RandomForest()
	{
		//dynamic polymorphism
		forest_trees[0] = new SkillTree();
		forest_trees[1] = new EducationTree();
		forest_trees[2] = new ProjectTree();
	}
	~RandomForest()
	{
		for (int i = 0; i < 3; i++)
			delete forest_trees[i];
	}

	void predict_job(Candidate* c)
	{
		int ds_v = 0, web_v = 0, game_v = 0, app_v = 0;
		title("ALGORITHM: RANDOM FOREST MAJORITY VOTE");

		for (int i = 0; i < 3; i++)
		{
			const char* vote_result = forest_trees[i]->vote(c);
			setColor(10);
			cout << "[Tree " << i + 1 << "] Result: " << vote_result << endl;
			setColor(7);

			if (string_compare(vote_result, "DATA SCIENTIST")) ds_v++;
			else if (string_compare(vote_result, "WEB DEVELOPER")) web_v++;
			else if (string_compare(vote_result, "GAME DEVELOPER")) game_v++;
			else if (string_compare(vote_result, "APP DEVELOPER")) app_v++;
		}

		line('-', 70);
		cout << "VOTE TALLY -> DS: " << ds_v << " | WEB: " << web_v << " | GAME: " << game_v << " | APP: " << app_v << endl;
		line('-', 70);

		int max_votes = 0;
		if (ds_v > max_votes)
			max_votes = ds_v;
		if (web_v > max_votes)
			max_votes = web_v;
		if (game_v > max_votes)
			max_votes = game_v;
		if (app_v > max_votes)
			max_votes = app_v;

		int tie_count = 0;
		if (ds_v == max_votes && max_votes > 0) tie_count++;
		if (web_v == max_votes && max_votes > 0) tie_count++;
		if (game_v == max_votes && max_votes > 0) tie_count++;
		if (app_v == max_votes && max_votes > 0) tie_count++;

		setColor(10);
		if (tie_count > 1)
		{
			cout << "\nFINAL STATUS: VERSATILE IT SPECIALIST" << endl;
			setColor(7);
			cout << "You have potential in these domains: " << endl;
			setColor(14);
			if (ds_v == max_votes) cout << "   - Data Science" << endl;
			if (web_v == max_votes) cout << "   - Web Development" << endl;
			if (game_v == max_votes) cout << "   - Game Development" << endl;
			if (app_v == max_votes) cout << "   - App Development" << endl;
		}
		else if (max_votes > 0)
		{
			const char* winner = "";
			if (ds_v == max_votes) winner = "DATA SCIENTIST";
			else if (web_v == max_votes) winner = "WEB DEVELOPER";
			else if (game_v == max_votes) winner = "GAME DEVELOPER";
			else if (app_v == max_votes) winner = "APP DEVELOPER";

			cout << "\nFINAL PREDICTED ROLE: " << winner << " (" << (max_votes / 3.0) * 100 << "%)" << endl;
		}
		else
		{
			setColor(12);
			cout << "\nSTATUS: INSUFFICIENT DATA (Add more specific skills/projects)" << endl;
		}
		setColor(7);
	}
};


int main()
{
	char FILE_NAME_PATH[100];
	Candidate candidate__obj;
	RandomForest PRIDICTOR;

	title("WELCOME TO THE JOB PREDICTION APPLICATION");
	cout << "REQUIRED FORMAT:\nNAME: ...\nAGE: ...\nEDUCATION: ...\nSKILLS: Name|Months, Name|Months\nPROJECTS: Title|Description\nCERTIFICATIONS: ...\n";

	cout << "\nENTER YOUR RESUME FILE PATH: ";
	cin.getline(FILE_NAME_PATH, 100);
	cout << endl;
	string path(FILE_NAME_PATH);
	path.erase(path.find_last_not_of(" \n\r\t") + 1);

	ifstream Read_file(path.c_str());
	if (!Read_file)
	{
		setColor(12);
		cout << "FILE ERROR: Could not open '" << FILE_NAME_PATH << "'. Check the path and extension.\n";
		setColor(7);
		return 0;
	}

	char LINE[1000];
	while (Read_file.getline(LINE, 1000))
	{
		int colon_pos = -1;
		for (int i = 0; LINE[i] != '\0'; i++)
		{
			if (LINE[i] == ':')
			{
				colon_pos = i;
				break;
			}
		}

		if (colon_pos != -1)
		{
			LINE[colon_pos] = '\0';
			char* KEY = LINE;
			char* VALUE = &LINE[colon_pos + 1];

			trim_spaces(KEY);
			trim_spaces(VALUE);

			if (string_compare(KEY, "NAME"))
				candidate__obj.set_name(VALUE);

			else if (string_compare(KEY, "AGE"))
				candidate__obj.set_age(atoi(VALUE));

			else if (string_compare(KEY, "EDUCATION"))
				candidate__obj.get_cv()->set_education(VALUE);

			else if (string_compare(KEY, "CERTIFICATIONS"))
				candidate__obj.get_cv()->set_certifications(VALUE);

			else if (string_compare(KEY, "SKILLS"))
			{
				char* skill_segment = VALUE;
				while (skill_segment != nullptr)
				{
					char* next_comma = strchr(skill_segment, ',');
					if (next_comma) *next_comma = '\0';

					char* pipe_pos = strchr(skill_segment, '|');
					if (pipe_pos)
					{
						*pipe_pos = '\0';
						char* s_name = skill_segment;
						int s_months = atoi(pipe_pos + 1);

						trim_spaces(s_name);
						if (strlen(s_name) > 0)
							candidate__obj.get_cv()->add_skill(s_name, s_months);
					}

					if (next_comma)
						skill_segment = next_comma + 1;
					else skill_segment = nullptr;
				}
			}
			else if (string_compare(KEY, "PROJECTS"))
			{
				char* pipe = strchr(VALUE, '|');
				if (pipe)
				{
					*pipe = '\0';
					char* p_title = VALUE;
					char* p_desc = pipe + 1;
					trim_spaces(p_title);
					trim_spaces(p_desc);
					candidate__obj.get_cv()->add_project(p_title, p_desc);
				}
			}
		}
	}
	Read_file.close();

	title("CANDIDATE DETAILS");
	candidate__obj.display_candidate();
	PRIDICTOR.predict_job(&candidate__obj);
	return 0;
}