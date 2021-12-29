# averkocpp
centria cpp end project

# Tommi Hellsten 29.12.2021
# centria cpp-ohjelmointi lopputyö

Lyhyesti:
Sovellus on C++-konversio LUT(Lappeenrannan-Lahden teknillinen yliopisto):n kesän 2021 pyhtonilla tehdyn ohjelmoinnin perusteet kurssin harjoitustyöstä.
Sovelluksen tehtävänä on lukea tekstimuotoon tallennettua aurinkopaneelien keruudataa ja laskea näistä halutut arvot.

Sovellus suoritetaan kutsumalla sitä komentoriviltä ilman parametrejä tai argumenttejä.
Sovelluksen käyttöliittymä on valikkopohjainen ja sitä ohjataan numerovalinnoilla komentoriviltä.
	
Käyttöliittymä:
	Mitä haluat tehdä:
	1) Lue tiedosto
	2) Analysoi tiedot
	3) Tallenna tulokset
	4) Päiväanalyysi
	5) Kuukausianalyysi
	6) Tuntianalyysi
	7) Kumulatiivinen päiväanalyysi
	0) Lopeta
	Valintasi:
	
Valinta 1) kysyy luettavan tiedoston nimeä ja lataa sen sisällön muistiin (olioina vektoritaulokkoon). Tiedoston avauksen tai luvun epäonnistuessa sovellus tulostaa virheilmoituksen ja sulkee itsensä.

Esimerkkiajo:
	Valintasi: 1
	Anna luettavan tiedoston nimi: data15.txt
	Tiedosto 'data15.txt' luettu.

Valinta 2) on käytettävissä vasta kuin tiedosto on luettu. Jos tiedostoa ei ole luettu, se palauttaa käyttäjän päävalikkoon. Jos tiedosto on luettu, valinta laskee analysyyit ja kirjaa ne merkkijonoina ylös vektoritaulokkoon. Analyysin jälkeen ohjelma tulostaa ruudulle käsiteltyjen alkioiden määrän ja aikavälin, jolta ne ovat.

Esimerkkiajo:
	Valintasi: 2
	Analyysi tehty, analysoitiin 15 data-alkiota.

Valinta 3) on käytettävissä valintojen 1 ja 2 jälkeen. Se kysyy tallennettavan tiedoston nimeä ja tulostaa tiedot ensin ruudulle ja sen jälkeen tiedostoon. Tämä siksi, jotta tulokset näkyvät ruudulla, vaikka tiedoston luonti epäonnistuisi.

Esimerkkiajo:
	Valintasi: 3
	Anna kirjoitettavan tiedoston nimi: test.txt
	Analysoitiin tiedosto data15.txt, jossa oli 15 auringonpaistetietoa väliltä 31.05.2018 - 01.06.2018
	Aurinko paistoi yhteensä 8 tuntia.
	Keskimäärin aurinko paistoi 8 tuntia päivässä.
	Aurinko paistoi eniten 01.06.2018 06:00, jolloin se paistoi 60 minuuttia tunnissa.
	Aurinko paistoi vähiten 01.06.2018 01:00, jolloin se paistoi 5 sekuntia tunnissa.
	Tulokset tallennettu tiedostoon 'test.txt'.

Valintojen 1, 2, 3 tiedoston käsittelysylki on toistettavissa useille eri tiedoistoille yhden sovelluksen ajokerran aikana niin haluttaessa.

Valinnat 4-7 ovat erikoistuneempia analyyseja, jotka luovat etukäteen määriteltyjä .csv tiedostoja esim. Excel grafiikan piirtoa varten.

Valinta 4) laskee auringonpaisteen määrän minuutteeina joka päivälle ja tulostaa ne "paiva.csv" tiedostoon.

Esimerkkiajo:
	Valintasi: 4
	Päiväanalyysi tehty.

	paiva.csv:
		Pvm;Paisteaika (m)
		31.05.2018;8
		01.06.2018;472

Valinta 5) laskee auringonpaisteen määrän tunteina joka kuukaudelle ja tulostaa ne "kuukausi.csv" tiedostoon.

Esimerkkiajo:
	Valintasi: 5
	Kuukausianalyysi tehty.
	
	kuukausi.csv:
		Kuukausi;Paisteaika (h)
		May;0
		Jun;7
		
Valinta 6) laskee auringopaisteen jakautuman eri tunneille koko keruujakson yli ja tulostaa sen "tunti.csv" tiedostoon.

Esimerkkiajo:
	Valintasi: 6
	Tuntianalyysi tehty.
	
	tunti.csv:
		Klo;Paisteaika (h)
		0;0
		1;0
		2;0
		...
		23;0
		
Valinta 7) laskee kumulatiivisen auringonpaisteen kertymän päivittäin ja tulostaa sen "kumulatiivinen.csv" tiedostoon.

Esimerkkiajo:
	Valintasi: 7
	Kumulatiivinen päiväanalyysi tehty.
	
	kumulatiivinen.csv:
		Pvm;Paisteaika (h)
		31.05.2018;0
		01.06.2018;8
		
----------------------------------------------------------------------------------------------------------------------

Ohjelma on kirjoitettu käyttäen Microsoft Visual Studio Code:a ja käännetty testiympäristössä (WSL2, Ubuntu 20.04 LTS)  komenolla

	g++ -Wall -g -std=c++11 main.cpp -o main.out
	
käyttäen g++:n (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 versiota ja todettu toimivan odotetusti ainakin odetulla syötteellä.

Sovellus on siis kirjoitettu käyttäen C++11 standardin mukaisia komentoja jne.

----------------------------------------------------------------------------------------------------------------------

Sovelluksen ohella on mukana testitiedostot data15.txt, data8700.txt ja data9700.txt, jotka olivat jaettu LUT:n opiskelijoille harjoitustyön testausta varten.

----------------------------------------------------------------------------------------------------------------------

Itsearviointi

Haastavinta työssä oli siirtyä Pythonin datetime-moduulista käyttämään C/C++ kielten struct tm ja time_t formaatteja. 
Funktiot ja metodit, joilla näitä käsitellään ovat siellä sun täällä. Lopputyössä käytetyt eri metodit tulevat useista
eri kirjastoista. std::get_time ja std::put_time ovat <iomanip> kirjastossa. std::difftime ja std::mktime ovat <ctime>
kirjastossa. Kriteerit näiden käyttöön ovat myös huomattavan tiukat. get_time ja put_time vaativat myös stringstream 
kirjaston eikä niitä voi käyttää suoraan merkkijonojen yhteydessä.

std::vector ja std::string kirjastot toisaalta antoivat käytännössä saman toiminnallisuuden kuin Pythonin listat ja
merkkijonot, mikä teki koodin "porttauksesta" helppoa muilta osin. Minulla on myös C:n perusteet kurssi takana, jonka 
ansiosta osoittimet ym. C:hen liittyvät konseptit eivät juurikaan pelottaneet tai aiheuttaneet ongelmia. Kiitos edellä
mainittujen <vector> ja <string> kirjastojen, näitä ei juurikaan tarvinnut pohtia.

Mietin kovasti olisiko työssä pitänyt käyttää "vector of pointers to objects" eli vektoria, joka koostuu osoittimista olioihin
"vector of objects" vektorin, joka koostuu olioista sijaan. Käytännön ero on, että jälkimmäinen vaatii yhtenäisen muistipaikan,
on helpompi koodata ja ylläpitää sekä nopeampi etsiä. Osoitinvektori on puolestaan paljon nopeampi tilanteessa, jossa vektoria
itseään muunnetaan ja järjesteellään uudelleen. Sekä kykenevä hyödyntämään muistitilaa, joka ei ole yhtäjaksoinen.
https://www.cppstories.com/2014/05/vector-of-objects-vs-vector-of-pointers/ [Viitattu 29.12.2021]

Tässä tapauksessa alkioiden järjestystä ei muutella ja jos oletetaan, että muistitila ei ole ongelma on nykyinen ratkaisu siis
tehokkaampi. Oliot joihin ositinvektori viittaisi täytysi myös vapauttaa muistista erikseen delete komenolla jokaista olioita
kohden. Kun oliot ovat suoraan vektorin sisällä, std::vector::clear vapauttaa myös oliot. Ositinvektorin tuhoaminen näin
poistaisi vain osoittimet jättäen dynaamisesti varatut oliot muistiin.

Toinen asia, mitä pohdin lyhyesti oli mahdollisuus siirtää ohjelmointiparagdimmiä enemmän olio-ohjelmoinnin suuntaan ja
kapsuloida funktoita luokkametodeiksi. Mietin myös mahdollisuutta kirjoittaa std::put_time kutsut luokkametodiksi, mutta 
eri analyysit halusivat erilaisia aikatageja, mikä vähensi hieman tämän hyödyllisyyttä. Viimeisenä mainittakoon, että C++11
olisi sallinut auto initilisaattorin käytön tyypin sijaan useissa kohdissa, mutta en nähnyt tätä olelliseeksi.

----------------------------------------------------------------------------------------------------------------------

LIITE

Alkuperäinen Python-lähdekoodi, jonka kirjoitin kesällä 2021.
#############################################################################################################
# 20210703 th
# HT.py
import HT_kirjasto

def menu():
    '''Main menu'''
    print("Mitä haluat tehdä:")
    print("1) Lue tiedosto")
    print("2) Analysoi tiedot")
    print("3) Tallenna tulokset")
    print("4) Päiväanalyysi")
    print("5) Kuukausianalyysi")
    print("6) Tuntianalyysi")
    print("7) Kumulatiivinen päiväanalyysi")
    print("0) Lopeta")
    slct = int(input("Valintasi: "))
    return slct

def paaohjelma():
    data = []
    results = []
    inputFile = ""
    while True:
        slct = menu()
        if (slct == 1):
            inputFile = input("Anna luettavan tiedoston nimi: ")
            data = HT_kirjasto.readFile(inputFile, data)
        elif (slct == 2):
            results = HT_kirjasto.analyzeData(inputFile, data, results)
        elif (slct == 3):
            HT_kirjasto.writeResults(results)
        elif (slct == 4):
            HT_kirjasto.dayAnalysis(data)
        elif (slct == 5):
            HT_kirjasto.monthAnalysis(data)
        elif (slct == 6):
            HT_kirjasto.hourlyAnalysis(data)
        elif (slct == 7):
            HT_kirjasto.cumulativeAnalysis(data)
        elif (slct == 0):
            break
        else:
            print("Valintaa ei tunnistettu, yritä uudestaan.")
        print()
    data.clear()
    results.clear()
    print("Kiitos ohjelman käytöstä.")      
    return None

paaohjelma()

# eof

###################################################################
# 20210703 th
# HT_kirjasto.py
# version 2.08
import datetime
import sys

hoursInADay = 24

class DATAENTRY:
    time = ""
    value = 0

def readFile(fileName, data):
    data.clear()
    try:
        file = open(fileName, "r")
        file.readline() # skip header row
        rowStr = file.readline()[:-1]
        row = []
        while True:
            if (rowStr == ""):
                break
            row = rowStr.split(";")
            entry = DATAENTRY()
            entry.value = int(row[2])
            entry.time = datetime.datetime.strptime(
                row[0] + " " + row[1], "%Y-%m-%d %H:%M")
            data.append(entry)
            rowStr = file.readline()[:-1]
        row.clear()
        file.close()
    except Exception:
        print("Tiedoston '" + fileName + "' käsittelyssä virhe, lopetetaan.")
        sys.exit(0)
    print("Tiedosto '" + fileName + "' luettu.")
    return data

def analyzeData(fileName, data, results):
    dataLen = len(data)
    if (dataLen != 0):
        results.clear()
        results.append("Analysoitiin tiedosto " + fileName + ", jossa oli " \
                        + str(dataLen) + " auringonpaistetietoa väliltä " + \
                        data[0].time.strftime("%d.%m.%Y") + \
                        " – " + data[-1].time.strftime("%d.%m.%Y."))
        # For perfomance reasons analyzes are done in the same loop if possible
        iMinVal = 0
        # Get a non-zero, non-negative initial min value if one exists
        for i in range(dataLen):
            if (data[iMinVal].value > 0):
                break
            iMinVal += 1
        iMaxVal = 0
        sumVal = 0
        for i in range(dataLen):
            sumVal += data[i].value
            if (0 < data[i].value and data[i].value < data[iMinVal].value):
                iMinVal = i
            elif (data[i].value > data[iMaxVal].value):
                iMaxVal = i
                
        results.append("Aurinko paistoi yhteensä " + str(int(sumVal / 3600)) + \
                       " tuntia.")

        daysDelta = (data[-1].time - data[0].time).days + 1
        avgVal = str(int(sumVal / daysDelta / 3600))
        results.append("Keskimäärin aurinko paistoi " + avgVal + \
                       " tuntia päivässä.")
        
        maxStr = "Aurinko paistoi eniten " + data[iMaxVal].time.strftime(
            "%d.%m.%Y kello %H:%M") + ", jolloin se paistoi " + \
            str(int(data[iMaxVal].value / 60)) + " minuuttia tunnissa."
        results.append(maxStr)
        
        minStr = "Aurinko paistoi vähiten " + data[iMinVal].time.strftime(
            "%d.%m.%Y kello %H:%M") + ", jolloin se paistoi " + \
            str(data[iMinVal].value) + " sekuntia tunnissa."
        results.append(minStr)

        print("Analyysi tehty, analysoitiin", dataLen, "data-alkiota.")
    else:
        print("Lista on tyhjä. Lue tiedosto ennen analyysiä.")
    return results

def writeResults(results):
    resultsLen = len(results)
    if (resultsLen != 0):
        fileName = input("Anna kirjoitettavan tiedoston nimi: ")
        for i in range(resultsLen):
            print(results[i])
        try:
            file = open(fileName, "w")
            for i in range(resultsLen):
                file.write(results[i] + "\n")
            print("Tulokset tallennettu tiedostoon '" + fileName + "'.")
            file.close()
        except Exception:
            print("Tiedoston '" + fileName + \
                  "' käsittelyssä virhe, lopetetaan.")
            sys.exit(0)            
    else:
        print("Ei tuloksia. Analysoi data ennen tallennusta.")
    return None

def writeCsv(fileName, results):
    try:
        file = open(fileName, "w")
        for i in range(len(results)):
            file.write(results[i] + "\n")
        file.close()
    except Exception:
        print("Tiedoston '" + fileName + \
              "' käsittelyssä virhe, lopetetaan.")
        sys.exit(0)            
    return None

def dayAnalysis(data):
    dataLen = len(data)
    if (dataLen != 0):
        dayList = ["Pvm;Paisteaika (m)",]

        dailyCumSum = data[0].value
        day = data[0].time.day
        for i in range(1, dataLen):
            if (day == data[i].time.day):
                dailyCumSum += data[i].value
            else:
                dailyCumSum = int(dailyCumSum / 60)
                outputStr = data[i - 1].time.strftime("%d.%m.%Y;") + \
                            str(dailyCumSum)
                dayList.append(outputStr)
                day = data[i].time.day
                dailyCumSum = data[i].value
        # "i + 1 loop", required to tally the final day.
        dailyCumSum = int(dailyCumSum / 60)
        outputStr = data[i - 1].time.strftime("%d.%m.%Y;") + \
                    str(dailyCumSum)
        dayList.append(outputStr)
        
        writeCsv("paiva.csv", dayList)
        dayList.clear()
        print("Päiväanalyysi tehty.")
    else:
        print("Lista on tyhjä. Lue tiedosto ennen analyysiä.")
    return None

def monthAnalysis(data):
    dataLen = len(data)
    if (dataLen != 0):
        monthlyList = ["Kuukausi;Paisteaika (h)",]
        
        # "Zeroth" loop as initial values
        monthlyCumSum = data[0].value
        month = data[0].time.month
        for i in range(1, dataLen):
            if (month == data[i].time.month):
                 monthlyCumSum += data[i].value
            else:
                monthlyCumSum = int(monthlyCumSum / 3600)
                outputStr = data[i - 1].time.strftime("%b;") + \
                            str(monthlyCumSum)
                monthlyList.append(outputStr)
                month = data[i].time.month
                monthlyCumSum = data[i].value
        # "i + 1 loop", required to tally the final month.
        # final test outside the loop for performance
        if (month == data[i - 1].time.month):
            monthlyCumSum = int(monthlyCumSum / 3600)
            outputStr = data[i - 1].time.strftime("%b;") + \
                        str(monthlyCumSum)
            monthlyList.append(outputStr)
        else: # edge case for when there's exactly one entry for the final month
            monthlyCumSum = int(monthlyCumSum / 3600)
            outputStr = data[i].time.strftime("%b;") + \
                        str(monthlyCumSum)
            monthlyList.append(outputStr)
        
        writeCsv("kuukausi.csv", monthlyList)
        monthlyList.clear()
        print("Kuukausianalyysi tehty.")
    else:
        print("Lista on tyhjä. Lue tiedosto ennen analyysiä.")
    return None

def hourlyAnalysis(data):
    dataLen = len(data)
    if (dataLen != 0):
        hourList = ["Klo;Paisteaika (h)",]

        hourValues = [0] * hoursInADay 
        for i in range(dataLen):
            hour = int(data[i].time.strftime("%H"))
            hourValues[hour] += data[i].value

        for i in range(hoursInADay):
            hourSum = int(hourValues[i] / 3600)
            hourList.append(str(i) + ";" + str(hourSum))
        
        writeCsv("tunti.csv", hourList)
        hourValues.clear()
        hourList.clear()
        print("Tuntianalyysi tehty.")
    else:
        print("Lista on tyhjä. Lue tiedosto ennen analyysiä.")
    return None

def cumulativeAnalysis(data):
    dataLen = len(data)
    if (dataLen != 0):
        dayList = ["Pvm;Paisteaika (h)",]

        dailyCumSum = data[0].value
        day = data[0].time.day
        sumSoFar = 0
        for i in range(1, dataLen):
            if (day == data[i].time.day):
                dailyCumSum += data[i].value
            else:
                sumSoFar = int(dailyCumSum / 3600)
                outputStr = data[i - 1].time.strftime("%d.%m.%Y;") + \
                            str(sumSoFar)
                dayList.append(outputStr)
                day = data[i].time.day
                dailyCumSum += data[i].value
        # "i + 1 loop", required to tally the final day.
        dailyCumSum = int(dailyCumSum / 3600)
        outputStr = data[i - 1].time.strftime("%d.%m.%Y;") + \
                    str(dailyCumSum)
        dayList.append(outputStr)
        
        writeCsv("kumulatiivinen.csv", dayList)
        dayList.clear()
        print("Kumulatiivinen päiväanalyysi tehty.")
    else:
        print("Lista on tyhjä. Lue tiedosto ennen analyysiä.")
    return None

##########################################
# eof
