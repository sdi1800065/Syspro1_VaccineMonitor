#include "modules.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

inline bool exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char** argv) 
{  
    int i;
    if(argc!=5)
    {
        std::cout<<"ERROR missing arguments\n";
        return 1;
    }
    std::string inputfile;
    int bloomsize;
    for(i=1;i<argc;i++)
    {
        std::string temp=argv[i];
        if(temp=="-c")
        {
            if(argv[i+1]==nullptr)
            {
                std::cout<<"ERROR Expected name of file after -c\n";
                return 1;
            }
            inputfile=argv[i+1];
            if((inputfile.substr(inputfile.length()-4,inputfile.length())).compare(".txt"))
                std::cout<<"ERROR please give the extension .txt on the inputfile argument ,after -c\n";
        }
        else if(temp=="-b")
        {
            if(argv[i+1]==nullptr)
            {
                std::cout<<"ERROR expected size of bloomfilter after -b\n";
                return 1;
            }
            std::string temp2=argv[i+1];
            int j;
            for (j=0;j<temp2.length();j++)
            {
                if( temp2[j]<'0' || temp2[j]>'9')
                {
                    std::cout<<"ERROR invalid intiger after -b, characters were detected\n";
                    return 1;                   
                }
            }
            bloomsize=std::stoi(argv[i+1]);
        }
    }


  if(exists(inputfile)==0)
  {
      std::cout<<"ERROR inputfile doesnt exist \n";
      return 1;
  }
  std::cout<<"Please wait for everything to be stored\n";
  std::ifstream myfile(inputfile);
  
  HTHash filetable=HTCreate(7867);//Initialize with a size /prime numbers are better as a size/the hashtable is dynamic so if it need more it will allocate by itself.
  HTHash virustable=HTCreate(23);
  HTHash countriestable=HTCreate(23);
  
  std::string id,firstname,lastname,country,age,virus,vacinated,date;
  std::string line;



  while (std::getline(myfile, line))
  {
    
    std::istringstream iss(line); 
    if (!(iss >>id>>firstname>>lastname>>country>>age>>virus>>vacinated)) { break; } // error

    if(vacinated=="NO")
    {
        if(iss>>date)
        {
            std::cout<<"ERROR IN RECORD "<<line<<" Date after NO\n";
            continue;
        }else date=" ";
       
    }else if(!(iss>>date)){std::cout<<"ERROR:EXPECTED DATE AFTER YES\n";continue;};

  insert_records_file(filetable,virustable,countriestable,bloomsize,id,firstname,lastname,country,age,virus,vacinated,date);
  
  }
  myfile.close();

  std::cout<<"Everything is stored give user input\n";

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string firstelement;
    if(!(iss>>firstelement)){std::cout<<"Wrong Input\n";continue;};

     if(firstelement=="/vaccineStatusBloom")
     {
        Virus_structs*getvirus;
        void* getvoid;
        std::string virus,citizenID;
        if(!(iss>>citizenID>>virus)){std::cout<<"Wrong Input\n";continue;};
        if(!HTsearch(filetable,citizenID)){std::cout<<"ERROR:No record with this id\n";continue;};
        if((!is_number(citizenID))){std::cout<<"ERROR:given id is not a number\n";continue;};
        if(HTGet(virustable,virus,&getvoid)==0){std::cout<<"ERROR:THERE IS NO SUCH VIRUS \n";continue;}
        getvirus=(Virus_structs*)getvoid;
        if(getvirus->bloom->lookup(citizenID))std::cout<<"MAYBE\n";
        else std::cout<<"NOT VACCINATED \n";
        continue;

     }
     else if(firstelement=="/vaccineStatus")
     {
        Virus_structs *getvirus;
        void* getvoid;
        std::string virus,citizenID;
        if(!(iss>>citizenID)){std::cout<<"Wrong Input\n";continue;};
        if(!HTsearch(filetable,citizenID)){std::cout<<"ERROR:No record with this id\n";continue;};
        if((!is_number(citizenID))){std::cout<<"ERROR:given id is not a number\n";continue;};


        if((iss>>virus))
        {
            if(HTGet(virustable,virus,&getvoid)==0){std::cout<<"ERROR:NONE IS VACCINATED FOR THIS VIRUS / INVALID INPUT \n";continue;}
            getvirus=(Virus_structs*)getvoid;
            listnode*temp;
            
            if(temp=getvirus->vaccinated->search(std::stoi(citizenID))){std::cout<<"VACCINATED ON "<<temp->data<<"\n";continue;}
            else if(temp=getvirus->not_vaccinated->search(std::stoi(citizenID))){std::cout<<"NOT VACCINATED \n";continue;}
            
            std::cout<<"ERROR:THIS ID WAS NOT GIVEN \n";continue;
        }
        else
        {
            printeveything(virustable,citizenID);
        }
        continue;
     }
     else if(firstelement=="/populationStatus")
     {
        std::string secondelement,virus,date1,date2;
        void*getc;
        void*getv;
        if((iss>>secondelement))
            if(HTGet(countriestable,secondelement,&getc))
            {
                if(iss>>virus)
                    if(HTGet(virustable,virus,&getv))
                        if(iss>>date1>>date2)
                        {
                            Date date_1,date_2;
                            if(date_1.setdate(date1) && date_2.setdate(date2))
                            {
                                print_country_statistics(filetable,date_1,date_2,secondelement,getv);
                                continue;
                            }
                        }

                        
            }
            else
            {
                if(HTGet(virustable,secondelement,&getv))
                {    if(iss>>date1>>date2)
                    {
                        Date date_1,date_2;
                        if(date_1.setdate(date1) && date_2.setdate(date2))
                        {    
                            for (int i=0;i<countriestable->size;i++)
                            {
                                Hashnode *templist=countriestable[i].list;
                                while(templist!=NULL)
                                {
                                    print_country_statistics(filetable,date_1,date_2,templist->key,getv);
                                    templist=templist->Link;
                                }
                            }
                            continue;
                        }
                    }
                    
                }
            }
        
        std::cout<<"ERROR:INVALID ARGUMENTS OR virus/country GIVEN NOT IN THE SYSTEM (DATES MUST BE GIVEN THEY ARE NOT OPTIONAL d/m/y ex 1-12-2019)\n";
        continue;
     }
     else if(firstelement=="/popStatusByAge")
     {
        std::string secondelement,virus,date1,date2;
        void*getc;
        void*getv;
        if((iss>>secondelement))
            if(HTGet(countriestable,secondelement,&getc))
            {
                if(iss>>virus)
                    if(HTGet(virustable,virus,&getv))
                        if(iss>>date1>>date2)
                        {
                            Date date_1,date_2;
                            if(date_1.setdate(date1) && date_2.setdate(date2))
                            {
                                print_country_statistics_age(filetable,date_1,date_2,secondelement,getv);
                                continue;
                            }
                        }

                        
            }
            else
            {
                if(HTGet(virustable,secondelement,&getv))
                {    if(iss>>date1>>date2)
                    {
                        Date date_1,date_2;
                        if(date_1.setdate(date1) && date_2.setdate(date2))
                        {    
                            for (int i=0;i<countriestable->size;i++)
                            {
                                Hashnode *templist=countriestable[i].list;
                                while(templist!=NULL)
                                {
                                    print_country_statistics_age(filetable,date_1,date_2,templist->key,getv);
                                    templist=templist->Link;
                                }
                            }
                            continue;
                        }
                    }
                    
                }
            }
        
        std::cout<<"ERROR:INVALID ARGUMENTS OR virus/country GIVEN NOT IN THE SYSTEM (DATES MUST BE GIVEN THEY ARE NOT OPTIONAL d/m/y ex 1-12-2019)\n";
        continue;
     }
     else if(firstelement=="/insertCitizenRecord")
     {
        if (!(iss >>id>>firstname>>lastname>>country>>age>>virus>>vacinated)) { std::cout<<"ERROR: IN USER INPUT\n";continue; } // error

        if(vacinated=="NO")
        {
            if(iss>>date)
            {
                std::cout<<"ERROR IN RECORD "<<id<<" "<<firstname<<" "<<lastname<<" "<<country<<""<<age<<" "<<virus<<" "<<vacinated<<" "<<date<<" Date after NO\n";
                continue;
            }else date=" ";
       
        }else if(!(iss>>date)){std::cout<<"ERROR:EXPECTED DATE AFTER YES\n";continue;};
        Date d;
        if(!d.setdate(date)){std::cout<<"ERROR:INVALID DATE GIVEN\n";continue;}
        insert_records_user(filetable,virustable,countriestable,bloomsize,id,firstname,lastname,country,age,virus,vacinated,date);
        continue; 
     }else if(firstelement=="/vaccinateNow")
     {
        if (!(iss >>id>>firstname>>lastname>>country>>age>>virus)) { std::cout<<"ERROR: IN USER INPUT\n";continue; } // error

        vacinated="YES";
        date="          ";
        get_todays_date(date);
        insert_records_user(filetable,virustable,countriestable,bloomsize,id,firstname,lastname,country,age,virus,vacinated,date);
        continue;
     }
     else if(firstelement=="/list-nonVaccinated-Persons")
     {
        if(!(iss>>virus)) { std::cout<<"ERROR: IN USER INPUT\n";continue; } // error
        void*getvoid;
        if(HTGet(virustable,virus,&getvoid))
        {
            print_all_nonvaccinated(filetable,getvoid);
            continue;
        }
        else
        {
            std::cout<<"ERROR:None is recorded for this virus\n";
            continue;
        }
     }
     else if(firstelement=="/exit")
     {
        break;
     }
     else
     {
        std::cout<<"WRONG USER INPUT\n";
     }
  }
  

  HTDestroy<records *>(filetable);
  HTDestroy<Virus_structs *>(virustable);

  HTDestroy<int*>(countriestable);//Doesnt matter what template you give couse item->data will be null for this case just need to delete pointers and key.

return 0;
} 