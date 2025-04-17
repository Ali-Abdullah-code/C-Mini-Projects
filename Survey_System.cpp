#include <iostream>
// #include <cctype>
#include <cstring>
#include <string>
using namespace std;

int my_strlen(const char *str)
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

int StoI(const char *str)
{
    if (str == nullptr || str[0] == '\0')
    {
        return 0;
    }

    int length = my_strlen(str);
    int number = 0;

    for (int i = 0; i < length; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            number = number * 10 + (str[i] - '0');
        }
        else
        {
            cout << "Error: Non-numeric character detected in StoI()" << endl;
            return 0;
        }
    }

    return number;
}

void my_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

class SurveyForm
{
public:
    int ID;
    char *name;
    char *date;

    SurveyForm() : ID(0)
    {
        name = new char[20];
        date = new char[20];
    }

    void SetSurvey()
    {
        char temp[200];
        int length;
        cout << "Enter ID of Survey: ";
        cin >> ID;
        cin.ignore();

        cout << "Enter name of Survey: ";
        cin.getline(temp, 200);
        length = my_strlen(temp) + 1;

        delete[] name;
        name = new char[length];
        my_strcpy(name, temp);

        cout << "Enter Date of Survey (D-M-Y): ";
        cin.getline(temp, 200);
        length = my_strlen(temp) + 1;

        delete[] date;
        date = new char[length];
        my_strcpy(date, temp);
    }

    void getSurvey()
    {
        cout << "Survey ID: " << ID << endl
             << "Name: " << name << endl
             << "Date: " << date << endl;
    }

    ~SurveyForm()
    {
        delete[] name;
        delete[] date;
    }
};

class Question
{
public:
    enum QuestionType
    {
        multiple_choice = 1,
        text_input,
        rating
    };

    int NumberOfQuestion;
    char **questionsARR;
    int *questionType;
    char ***optionsArr;
    int *optionCounts;

    Question() : NumberOfQuestion(0)
    {
        questionsARR = nullptr;
        questionType = nullptr;
        optionsArr = nullptr;
        optionCounts = nullptr;
    }

    void MakeQuestion()
    {
        cout << "Enter Number of Questions: ";
        cin >> NumberOfQuestion;
        cin.ignore();

        questionsARR = new char *[NumberOfQuestion];
        questionType = new int[NumberOfQuestion];
        optionsArr = new char **[NumberOfQuestion];
        optionCounts = new int[NumberOfQuestion];

        for (int i = 0; i < NumberOfQuestion; i++)
        {
            cout << "Enter Type of Question (1: Multiple Choice, 2: Text Input, 3: Rating): ";
            cin >> questionType[i];
            cin.ignore();

            char temp[200];
            cout << "Enter question " << i + 1 << ": ";
            cin.getline(temp, 200);
            int length = my_strlen(temp) + 1;
            questionsARR[i] = new char[length];
            my_strcpy(questionsARR[i], temp);

            if (questionType[i] == multiple_choice)
            {
                int options;
                cout << "Enter number of options: ";
                cin >> options;
                cin.ignore();

                optionCounts[i] = options;
                optionsArr[i] = new char *[options];

                for (int j = 0; j < options; j++)
                {
                    cout << "Enter option " << j + 1 << ": ";
                    cin.getline(temp, 200);
                    int optLength = my_strlen(temp) + 1;
                    optionsArr[i][j] = new char[optLength];
                    my_strcpy(optionsArr[i][j], temp);
                }
            }
            else
            {
                optionCounts[i] = 0;
                optionsArr[i] = nullptr;
            }
        }

        cout << "Questions saved successfully!\n";
    }

    ~Question()
    {
        for (int i = 0; i < NumberOfQuestion; i++)
        {
            delete[] questionsARR[i];
        }
        delete[] questionsARR;

        for (int i = 0; i < NumberOfQuestion; i++)
        {
            if (questionType[i] == multiple_choice && optionsArr[i] != nullptr)
            {
                for (int j = 0; j < optionCounts[i]; j++)
                {
                    delete[] optionsArr[i][j];
                }
                delete[] optionsArr[i];
            }
        }
        delete[] optionsArr;
        delete[] questionType;
        delete[] optionCounts;
    }
};

class Answer
{
public:
    char **AnswerOfUser;
    Question *questions;

    Answer(Question *q) : AnswerOfUser(nullptr), questions(q)
    {
        if (q == nullptr)
        {
            cout << "The Question Pointer cann't be NULL" << endl;
        }
    }

    void inputAnswer()
    {
        if (questions == nullptr || questions->NumberOfQuestion == 0)
        {
            cout << "No survey available. Ask the admin to create one.\n";
            return;
        }

        AnswerOfUser = new char *[questions->NumberOfQuestion];

        cout << "\nSurvey Questions:\n";
        for (int i = 0; i < questions->NumberOfQuestion; i++)
        {
            cout << i + 1 << ". " << questions->questionsARR[i] << endl;

            if (questions->questionType[i] == questions->multiple_choice)
            {
                cout << "Select an option (Enter the text of the chosen option):\n";
                for (int j = 0; j < questions->optionCounts[i]; j++)
                {
                    cout << "  " << j + 1 << ". " << questions->optionsArr[i][j] << endl;
                }
            }
            else if (questions->questionType[i] == questions->rating)
            {
                cout << "Rate on a scale from 1 to 5: ";
            }
            else
            {
                cout << "Enter your text answer: ";
            }

            char temp[200];
            cin.getline(temp, 200);

            int length = my_strlen(temp) + 1;
            AnswerOfUser[i] = new char[length];
            my_strcpy(AnswerOfUser[i], temp);
        }
    }

    ~Answer()
    {
        for (int i = 0; i < questions->NumberOfQuestion; i++)
        {
            delete[] AnswerOfUser[i];
        }
        delete[] AnswerOfUser;
    }
};

class User
{
public:
    Answer *answer;
    char name[20]{};

    User() : answer(nullptr) {}

    void LoginUser(Question *existingQuestion)
    {
        if (existingQuestion == nullptr)
        {
            cout << "No survey questions available!\n";
            return;
        }
        cout << "Enter name: ";
        cin.getline(name, 20);

        answer = new Answer(existingQuestion);

        answer->inputAnswer();
        cout << "\nThanks for Feedback\n";
    }
};

class Report
{
public:
    Question *question;
    Answer *answer;
    char **listTextData;
    static int count;
    int yes, No, rating, ratingcount;

    Report(Question *q, Answer *a) : question(q), answer(a), yes(0), No(0), rating(0), ratingcount(0)
    {

        listTextData = new char *[question->NumberOfQuestion];
        for (int i = 0; i < question->NumberOfQuestion; i++)
        {
            listTextData[i] = nullptr;
        }
    }

    void GenerateResponse()
    {
        for (int i = 0; i < question->NumberOfQuestion; i++)
        {
            if (question->questionType[i] == question->multiple_choice)
            {

                char *response = answer->AnswerOfUser[i];

                if (my_strlen(response) >= 2)
                {
                    if ((response[0] == 'Y' || response[0] == 'y') && response[1] == 'e')
                    {
                        yes++;
                    }
                    else if ((response[0] == 'N' || response[0] == 'n') && response[1] == 'o')
                    {
                        No++;
                    }
                }
            }
            else if (question->questionType[i] == question->rating)
            {
                int userRating = StoI(answer->AnswerOfUser[i]); // Convert string to int
                if (userRating >= 1 && userRating <= 5)
                {
                    rating += userRating;
                    ratingcount++;
                }
            }
            else
            {
                {
                    int length = my_strlen(answer->AnswerOfUser[i]) + 1;
                    listTextData[i] = new char[length];
                    my_strcpy(listTextData[i], answer->AnswerOfUser[i]);
                }
            }
        }

        cout << "\nResponse Generated: " << endl;
        cout << "Yes: " << yes << endl;
        cout << "No: " << No << endl;
        if (ratingcount > 0)
        {
            cout << "Total Rating: " << (float)rating / ratingcount << endl;
        }
        else
        {
            cout << "No Ratings Given" << endl;
        }
        count++;
    }

    void ReportGenerate()
    {
        cout << "\nSurvey Report " << endl;
        cout << "--------------------------------" << endl;
        cout << "Total Responses Collected: " << count << endl;
        cout << "Yes Responses: " << yes << endl;
        cout << "No Responses: " << No << endl;

        if (ratingcount > 0)
        {
            cout << "Average Rating: " << (float)rating / ratingcount << endl;
        }
        else
        {
            cout << "No Ratings Given" << endl;
        }

        cout << "\nText Responses: " << endl;
        for (int i = 0; i < question->NumberOfQuestion; i++)
        {
            if (listTextData[i] != nullptr)
            {
                cout << "- " << listTextData[i] << endl;
            }
        }
    }

    ~Report()
    {
        for (int i = 0; i < question->NumberOfQuestion; i++)
        {
            delete[] listTextData[i];
        }
        delete[] listTextData;
    }
};

int Report::count = 0;

class Admin
{
public:
    Answer *a;
    Report *report;
    Question *question;
    SurveyForm *surveys;
    int surveyCount;
    int capacity;

    Admin()
    {
        a = nullptr;
        report = nullptr;
        question = nullptr;
        surveys = nullptr;
        capacity = 2;
        surveys = new SurveyForm[capacity];
        surveyCount = 0;
    }

    ~Admin()
    {
        delete a;
        delete report;
        delete question;
        delete[] surveys;
    }

    void AdminLogin()
    {
        cout << "Enter name: ";
        string tempName;
        getline(cin, tempName);
        cout << "Enter password: ";
        string tempPassword;
        getline(cin, tempPassword);
        if (tempName != "admin" || tempPassword != "1234")
        {
            cout << "Wrong Credentials Entered" << endl;
            return;
        }
        int choice;
        do
        {
            cout << "\n<<----- Admin Panel ----->>\n";
            cout << "1. Create New Survey\n";
            cout << "2. Manage Questions\n";
            cout << "3. View Responses\n";
            cout << "4. Generate Reports & Analytics\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
                CreateSurvey();
                break;
            case 2:
                ManageQuestions();
                break;
            case 3:
                ViewResponses();
                break;
            case 4:
                GenerateReport();
                break;
            case 5:
                cout << "Logging Out...\n";
                break;
            default:
                cout << "Invalid Choice! Try again.\n";
            }
        } while (choice != 5);
    }

    void CreateSurvey()
    {
        if (surveyCount >= capacity)
        {
            ResizeArray();
        }
        surveys[surveyCount].SetSurvey();
        surveyCount++;
        cout << "Survey Created Successfully!\n";
    }

    void ManageQuestions()
    {
        if (surveyCount == 0)
        {
            cout << "No Surveys Available!\n";
            return;
        }
        if (question == nullptr)
        {
            question = new Question();
        }
        question->MakeQuestion();
    }

    void ViewResponses()
    {
        if (surveyCount == 0)
        {
            cout << "No Surveys Available!\n";
            return;
        }
        if (report == nullptr)
        {
            report = new Report(question, a);
        }
        report->GenerateResponse();
    }

    void GenerateReport()
    {
        if (surveyCount == 0)
        {
            cout << "No Surveys Available!\n";
            return;
        }
        if (report == nullptr)
        {
            report = new Report(question, nullptr);
        }
        report->ReportGenerate();
    }
    void StoreAnswers(Answer *userAnswer)
    {
        if (report == nullptr)
        {
            report = new Report(question, userAnswer);
        }
        else
        {
            delete report;
            report = new Report(question, userAnswer);
        }
    }

private:
    void ResizeArray()
    {
        int newCapacity = capacity * 2;
        SurveyForm *newSurveys = new SurveyForm[newCapacity];

        for (int i = 0; i < surveyCount; i++)
        {
            newSurveys[i] = surveys[i];
        }

        delete[] surveys;
        surveys = newSurveys;
        capacity = newCapacity;
    }
};

int main()
{

    int choice;
    Admin a1;

    while (true)
    {
        cout << "\nSelect Role:\n"
             << "1. Admin\n"
             << "2. User\n"
             << "3. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            a1.AdminLogin();
        }
        else if (choice == 2)
        {
            if (a1.question == nullptr || a1.question->NumberOfQuestion == 0)
            {
                cout << "No survey available. Ask the admin to create one.\n";
                continue;
            }
            cout << "Enter number of Users that want: ";
            int number;
            cin >> number;
            cin.ignore();
            User *UserArray = new User[number];
            for (int i = 0; i < number; i++)
            {
                UserArray[i].LoginUser(a1.question);
                a1.StoreAnswers(UserArray[i].answer);
            }
            delete[] UserArray;
        }
        else if (choice == 3)
        {
            cout << "\nExiting the Program...\n";
            break;
        }
        else
        {
            cout << "\nInvalid Choice! Please select again.\n";
        }
    }

    return 0;
}
