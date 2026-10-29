#include <iostream>
#include <cmath>

int main();

int main()
{
    //intializations
  
    //intialized all of them to negative so that it fails the first test 
    //allows me to type the text once instead of multiple times 
    //grade max
    double midTermMax{-1};
    double finalExamM{-1};
    double project1M{-1};
    double project2M{-1};
    double project3M{-1};
    double project4M{-1};
    double project5M{-1};

    //grades recieved
    double midTermGrade{-2};
    double final_Exam_Grade{-2};
    double p1Grade{-2};
    double p2Grade{-2};
    double p3Grade{-2};
    double p4Grade{-2};
    double p5Grade {-2};
    
    double examWeight{-1};
    double projectWeight{-1};
    double fGrade{-1};
    //ask about final exam
    do
    {
        std::cout << "Enter maximum grade on the final examination: ";
        std::cin >> finalExamM;
    }
    while(finalExamM <= 0 || finalExamM != std::round(finalExamM));//checks if the value isn't less than 0 and if it's an integer if its not it will run again
    do
    {
        std::cout << "Enter your grade on the final examination: ";
        std::cin >> final_Exam_Grade;
    }
    while(final_Exam_Grade < 0 || final_Exam_Grade > finalExamM);//checks if the grade on the final exam isn't greater than the max points and isn't less than 0

    //ask about midterm
    do
    {
        std::cout << "Enter maximum grade on the mid-term examination: ";
        std::cin >> midTermMax;
    } while (midTermMax <= 0 || midTermMax != std::round(midTermMax));
    do
    {
        std::cout << "Enter your grade on the mid-term examination:";
        std::cin >> midTermGrade;
    } while (midTermGrade < 0 || midTermGrade > midTermMax);    

    //ask about projects
    //project 1
    do
    {
        std::cout << "Enter maximum grade on project 1: ";
        std::cin >> project1M;
    } while (project1M <= 0 || project1M != std::round(project1M));
    do
    {
        std::cout << "Enter your grade on project 1: ";
        std::cin >> p1Grade;
    } while (p1Grade < 0 || p1Grade > project1M);
    
    //project 2 
    do
    {
        std::cout << "Enter maximum grade on project 2: ";
        std::cin >> project2M;
    } while (project2M <= 0 || project2M != std::round(project2M));
    do
    {
        std::cout << "Enter your grade on project 2: ";
        std::cin >> p2Grade;
    } while (p2Grade < 0 || p2Grade > project2M);

    //project 3
    do
    {
        std::cout << "Enter maximum grade on project 3: ";
        std::cin >> project3M;
    } while (project3M <= 0 || project3M != std::round(project3M));
    do
    {
        std::cout << "Enter your grade on project 3: ";
        std::cin >> p3Grade;
    } while (p3Grade < 0 || p3Grade > project3M);

    //project 4
    do
    {
        std::cout << "Enter maximum grade on project 4: ";
        std::cin >> project4M;
    } while (project4M <= 0 || project4M != std::round(project4M));
    do
    {
        std::cout << "Enter your grade on project 4: ";
        std::cin >> p4Grade;
    } while (p4Grade < 0 || p4Grade > project4M);

    //project 5
    do
    {
        std::cout << "Enter maximum grade on project 5: ";
        std::cin >> project5M;
    } while (project5M <= 0 || project5M != std::round(project5M));
    do
    {
        std::cout << "Enter your grade on project 5: ";
        std::cin >> p5Grade;
    } while (p5Grade < 0 || p5Grade > project5M);


    final_Exam_Grade = ( 100.0 * final_Exam_Grade) / finalExamM;
    midTermGrade =  (100.0 * midTermGrade) / midTermMax;
    p1Grade = (100.0 * p1Grade) / project1M;
    p2Grade = (100.0 * p2Grade) / project2M;
    p3Grade = (100.0 * p3Grade) / project3M;
    p4Grade = (100.0 * p4Grade) / project4M;
    p5Grade = (100.0 * p5Grade) / project5M;
    
    if(final_Exam_Grade > midTermGrade)
    {
        midTermGrade = final_Exam_Grade;
    }
    if(final_Exam_Grade > p1Grade)
    {
        p1Grade = final_Exam_Grade;
    }
    if(final_Exam_Grade > p2Grade)
    {
        p2Grade = final_Exam_Grade;
    }
    if(final_Exam_Grade > p3Grade)
    {
        p3Grade = final_Exam_Grade;
    }
    if(final_Exam_Grade > p4Grade)
    {
        p4Grade = final_Exam_Grade;
    }
    if(final_Exam_Grade > p5Grade)
    {
        p5Grade = final_Exam_Grade;
    }
    
    examWeight = (0.75 * final_Exam_Grade) + (0.25 * midTermGrade);

    projectWeight = (p1Grade + p2Grade + p3Grade + p4Grade + p5Grade) / 5.0;
     
    if(examWeight <= 40)//full exam weight if exam
    {
        fGrade = examWeight;
    }
    else if(examWeight >= 60)
    {
        fGrade = ((2.0/3.0) * examWeight) + ((1.0/3.0) * projectWeight);
    }
    else
    {
        fGrade = (projectWeight * (1.0/3.0) * ((examWeight - 40.0) / 20.0)) + (examWeight) * (1.0 - ((1.0/3.0) * (examWeight - 40) / 20.0));
    }

    std::cout << "Final grade: "<< std::round(fGrade + 1e-12) << std::endl;
    
    return 0;
}
