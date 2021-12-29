/* 20211229 th, main.cpp */

#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

class Dataentry
{
    public:

    std::tm time;
    int nValue;

    Dataentry(std::tm time, int value)
    {
        this->time = time;
        this->nValue = value;
    }
};

/* https://coderedirect.com/questions/292333/c-converting-a-datetime-string-to-epoch-cleanly */
std::tm strToTime(std::string str);
void split(std::vector<std::string> &arrSplit, std::string str, char delim);
void readFile(std::string fileName, std::vector<Dataentry> &data);
void analyzeData(std::string fileName, std::vector<Dataentry> &data, std::vector<std::string> &results);
void writeResults(std::vector<std::string> &results);
void writeCsv(std::string fileName, std::vector<std::string> &dataList);
void dayAnalysis(std::vector<Dataentry> &data);
void monthAnalysis(std::vector<Dataentry> &data);
void hourlyAnalysis(std::vector<Dataentry> &data);
void cumulativeAnalysis(std::vector<Dataentry> &data);

int menu()
{
    std::cout << "Mitä haluat tehdä:\n";
    std::cout << "1) Lue tiedosto\n";
    std::cout << "2) Analysoi tiedot\n";
    std::cout << "3) Tallenna tulokset\n";
    std::cout << "4) Päiväanalyysi\n";
    std::cout << "5) Kuukausianalyysi\n";
    std::cout << "6) Tuntianalyysi\n";
    std::cout << "7) Kumulatiivinen päiväanalyysi\n";
    std::cout << "0) Lopeta\n";
    std::cout << "Valintasi: ";
    int x;
    std::cin >> x;
    return x;
}

int main()
{
    std::vector<Dataentry> data = {};
    std::vector<std::string> results = {};
    std::string fileName;
    int nSelect;
    while(true)
    {
        nSelect = menu();
        if(nSelect == 1)
        {
            std::cout << "Anna luettavan tiedoston nimi: ";
            std::cin >> fileName;
            readFile(fileName, data);
        }
        else if(nSelect == 2)
        {
            analyzeData(fileName, data, results);
        }
        else if(nSelect == 3)
        {
            writeResults(results);
        }
        else if(nSelect == 4)
        {
            dayAnalysis(data);
        }
        else if(nSelect == 5)
        {
            monthAnalysis(data);
        }
        else if(nSelect == 6)
        {
            hourlyAnalysis(data);
        }
        else if(nSelect == 7)
        {
            cumulativeAnalysis(data);
        }
        else if(nSelect == 0){
            break ;
        }
        else
        {
            std::cout << "Valintaa ei tunnistettu, yritä uudestaan.\n";
        }
        std::cout << "\n";
    }
    std::cout << "Kiitos ohjelman käytöstä.\n";
    data.clear();
    results.clear();
    return 0;
}

std::tm strToTime(std::string str)
{
    std::tm t = {};
    std::istringstream ss(str);

    if (ss >> std::get_time(&t, "%Y-%m-%d %H:%M")){}
    else
    {
        std::cout << "Virheellinen aikaformaatti.\n";
        exit(0);
    }
    return t;
}

void split(std::vector<std::string> &arrSplit, std::string str, char delim)
{   
    arrSplit.clear();
    std::string temp = "";

    for (std::size_t i = 0; i < str.size(); i++){
        if (str[i] != delim)
        {
            temp += str[i];
        }
        else
        {
            arrSplit.push_back(temp);
            temp = "";
        }
    }
    arrSplit.push_back(temp);
}

void readFile(std::string fileName, std::vector<Dataentry> &data)
{
    data.clear();
    std::string line;
    std::ifstream datafile (fileName);
    if (datafile.is_open())
    {
        std::vector<std::string> lineParts = {};
        std::getline (datafile, line);
        while (std::getline (datafile, line))
        {
            if (line.length() > 2)
            {
                split(lineParts, line, ';');
                std::string timeTag = lineParts[0] + " " + lineParts[1];
                std::tm time = {0};
                time = strToTime(timeTag);

                int value = stoi(lineParts[2]);

                data.push_back(Dataentry(time, value));
            }            
        }
        lineParts.clear();
        datafile.close();
    }
    else 
    {
        std::cout << "Tiedoston '" << fileName << "' käsittelyssä virhe, lopetetaan.\n";
        exit(0);
    }
    std::cout << "Tiedosto '" << fileName << "' luettu.\n";
}

void analyzeData(std::string fileName, std::vector<Dataentry> &data, std::vector<std::string> &results)
{
    std::size_t datalen = data.size();
    if (datalen != 0)
    {
        results.clear();
        std::stringstream ss;
        ss << "Analysoitiin tiedosto " << fileName << ", jossa oli "
           << std::to_string(datalen)
           << " auringonpaistetietoa väliltä "
           << std::put_time(&data[0].time, "%d.%m.%Y")
           << " - "
           << std::put_time(&data[datalen - 1].time, "%d.%m.%Y");
        results.push_back(ss.str());
        ss.str(std::string());
        ss.clear();

        // positiivinen alkuarvo minimille.
        std::size_t minValIndex = 0;
        while (minValIndex < datalen)
        {
            if (data[minValIndex].nValue > 0)
            {
                break;
            }
            minValIndex++;
        }
        std::size_t maxValIndex = 0;
        int sumValue = 0;
        for (std::size_t i = 0; i < datalen; i++)
        {
            sumValue += data[i].nValue;
            if (0 < data[i].nValue && data[i].nValue < data[minValIndex].nValue)
            {
                minValIndex = i;
            }
            else if (data[i].nValue > data[maxValIndex].nValue)
            {
                maxValIndex = i;
            }
        }

        results.push_back("Aurinko paistoi yhteensä " + std::to_string(sumValue / 3600) + " tuntia.");

        double timeDeltaSeconds = std::difftime(std::mktime(&data[(datalen - 1)].time), std::mktime(&data[0].time));
        int timeDeltaDays = std::floor(timeDeltaSeconds / 86400) + 1;
        std::string avgValue = std::to_string(sumValue / timeDeltaDays / 3600);

        results.push_back("Keskimäärin aurinko paistoi " + avgValue +  " tuntia päivässä.");

        /* Verbose maximum value */
        ss << "Aurinko paistoi eniten "
           << std::put_time(&data[maxValIndex].time, "%d.%m.%Y %H:%M")
           << ", jolloin se paistoi "
           << std::to_string(data[maxValIndex].nValue / 60)
           << " minuuttia tunnissa.";
        results.push_back(ss.str());
        ss.str(std::string());
        ss.clear();

        /* Verbose minimum value */
        ss << "Aurinko paistoi vähiten "
           << std::put_time(&data[minValIndex].time, "%d.%m.%Y %H:%M")
           << ", jolloin se paistoi "
           << std::to_string(data[minValIndex].nValue)
           << " sekuntia tunnissa.";
        results.push_back(ss.str());
        ss.str(std::string());
        ss.clear();

        std::cout << "Analyysi tehty, analysoitiin "
                  << datalen
                  << " data-alkiota.\n";    
    }
    else {
        std::cout << "Lista on tyhjä. Lue tiedosto ennen analyysiä.\n";
    }
}

void writeResults(std::vector<std::string> &results)
{
    std::size_t resultsLen = results.size();
    if (resultsLen > 0)
    {
        std::string fileName;
        std::cout << "Anna kirjoitettavan tiedoston nimi: ";
        std::cin >> fileName;

        for (std::string& str: results)
        {
            std::cout << str << "\n";
        }

        std::ofstream outputFile(fileName);
        if (outputFile.is_open())
        {
            for (std::string& str: results)
            {
                outputFile << str << "\n";
            }
            outputFile.close();
            std::cout << "Tulokset tallennettu tiedostoon '" << fileName << "'.\n";
        }
        else
        {
            std::cout << "Tiedoston '" << fileName << "' käsittelyssä virhe, lopetetaan.\n";
            exit(0);
        }
    } 
    else
    {
        std::cout << "Ei tuloksia. Analysoi data ennen tallennusta.\n";
    }    
}

void writeCsv(std::string fileName, std::vector<std::string> &dataList)
{
    std::ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        for (std::string& str: dataList)
        {
            outputFile << str << "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Tiedoston '" << fileName << "' käsittelyssä virhe, lopetetaan.\n";
        exit(0);
    }
}

void dayAnalysis(std::vector<Dataentry> &data)
{
    std::size_t datalen = data.size();
    if (datalen > 0)
    {
        std::stringstream ss;
        std::vector<std::string> dayList = { "Pvm;Paisteaika (m)" };

        int dailyCumSum = data[0].nValue;
        int day = data[0].time.tm_mday;
        std::size_t i = 1;

        while (i < datalen)
        {
            if (day == data[i].time.tm_mday)
            {
                dailyCumSum += data[i].nValue;
            }
            else
            {
                dailyCumSum /= 60;
                ss << std::put_time(&data[i - 1].time, "%d.%m.%Y;")
                   << std::to_string(dailyCumSum);
                dayList.push_back(ss.str());
                ss.str(std::string());
                ss.clear();

                day = data[i].time.tm_mday;
                dailyCumSum = data[i].nValue;
            }
            i++;
        }
        dailyCumSum /= 60;
        ss << std::put_time(&data[i - 1].time, "%d.%m.%Y;")
           << std::to_string(dailyCumSum);
        dayList.push_back(ss.str());
        ss.str(std::string());
        ss.clear();

        writeCsv("paiva.csv", dayList);
        dayList.clear();
        std::cout << "Päiväanalyysi tehty.\n";
    }
    else
    {
        std::cout << "Lista on tyhjä. Lue tiedosto ennen analyysiä.\n";
    }
}

void monthAnalysis(std::vector<Dataentry> &data)
{
    std::size_t datalen = data.size();
    if (datalen > 0)
    {
        std::stringstream ss;
        std::vector<std::string> monthList = { "Kuukausi;Paisteaika (h)" };

        int monthlyCumSum = data[0].nValue;
        int month = data[0].time.tm_mon;
        std::size_t i = 1;

        while (i < datalen)
        {
            if (month == data[i].time.tm_mon)
            {
                monthlyCumSum += data[i].nValue;
            }
            else
            {
                monthlyCumSum /= 3600;
                ss << std::put_time(&data[i - 1].time, "%b;")
                   << std::to_string(monthlyCumSum);
                monthList.push_back(ss.str());
                ss.str(std::string());
                ss.clear();

                month = data[i].time.tm_mon;
                monthlyCumSum = data[i].nValue;
            }
            i++;
        }
        if (month == data[i - 1].time.tm_mon)
        {
            monthlyCumSum /= 3600;
            ss << std::put_time(&data[i - 1].time, "%b;")
               << std::to_string(monthlyCumSum);
            monthList.push_back(ss.str());
            ss.str(std::string());
            ss.clear();
        }
        else /* rajaustapaus, missä viimeinen alkio aloittaa uuden kuukauden */
        {
            monthlyCumSum /= 3600;
            ss << std::put_time(&data[i].time, "%b;")
               << std::to_string(monthlyCumSum);
            monthList.push_back(ss.str());
            ss.str(std::string());
            ss.clear();
        }
        
        writeCsv("kuukausi.csv", monthList);
        monthList.clear();
        std::cout << "Kuukausianalyysi tehty.\n";
    }
    else
    {
        std::cout << "Lista on tyhjä. Lue tiedosto ennen analyysiä.\n";
    }
}

void hourlyAnalysis(std::vector<Dataentry> &data)
{
    std::size_t datalen = data.size();
    if (datalen > 0)
    {
        std::vector<std::string> hourList = { "Klo;Paisteaika (h)" };

        std::vector<int> hourValues;
        hourValues.assign(24, 0);

        int hour;
        for (Dataentry& entry: data){
            hour = entry.time.tm_hour;
            hourValues[hour] += entry.nValue;
        }

        for (std::size_t i = 0; i < 24; i++)
        {
            hourList.push_back(std::to_string(i) + ";" + std::to_string(hourValues[i] / 3600));
        }

        writeCsv("tunti.csv", hourList);
        hourValues.clear();
        hourList.clear();
        std::cout << "Tuntianalyysi tehty.\n";
    }
    else
    {
        std::cout << "Lista on tyhjä. Lue tiedosto ennen analyysiä.\n";
    }    
}

void cumulativeAnalysis(std::vector<Dataentry> &data){
    std::size_t datalen = data.size();
    if (datalen > 0)
    {
        std::stringstream ss;
        std::vector<std::string> dayList = { "Pvm;Paisteaika (h)" };

        int dailyCumSum = data[0].nValue;
        int day = data[0].time.tm_mday;
        std::size_t i = 1;

        while (i < datalen)
        {
            if (day == data[i].time.tm_mday)
            {
                dailyCumSum += data[i].nValue;
            }
            else
            {
                ss << std::put_time(&data[i - 1].time, "%d.%m.%Y;")
                   << std::to_string(dailyCumSum / 3600);
                dayList.push_back(ss.str());
                ss.str(std::string());
                ss.clear();

                day = data[i].time.tm_mday;
                dailyCumSum += data[i].nValue;
            }
            i++;
        }
        dailyCumSum /= 3600;
        ss << std::put_time(&data[i - 1].time, "%d.%m.%Y;")
           << std::to_string(dailyCumSum);
        dayList.push_back(ss.str());
        ss.str(std::string());
        ss.clear();

        writeCsv("kumulatiivinen.csv", dayList);
        dayList.clear();
        std::cout << "Kumulatiivinen päiväanalyysi tehty.\n";
    }
    else
    {
        std::cout << "Lista on tyhjä. Lue tiedosto ennen analyysiä.\n";
    }
}

/* eof */