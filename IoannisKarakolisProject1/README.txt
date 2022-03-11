Καρακολης Ιωαννης Sdi1800065

Για το compilation:make
Για διαγραφη των αρχειων που δημιουργει το makefile : make clean

Για το bash:./testFile.sh virusesFile.txt countriesFile.txt 1000 1

Παρακαλω χρησιμοποιηστε τα αρχεια virusesFile.txt και countriesFile.txt που εχουν δωθει ,καθως το bashfile χρησιμοποιει
την εντολη mapfile και αν καποιο αρχειο απο αυτα δημιουργηθει δινοντας ιους/χωρες manualy πολυ πιθανο να διαβαστει και η 
αλλαγη γραμμης ,οδηγωντας την εγγραφη να εκτυπωθει σε παραπανω απο μια σειρα και να απορριφθει απο το προγραμμα.

Για την εκτελεση: ./vaccineMonitor -c inputFile.txt -b bloomsize

Μετα το διαβασμα των αρχειων και αφου εχει εκτυπωθει το μυνημα "Everything is stored." 
μπορουν να δωθουν οι εντολες οπως αναφαιρονται στην εκφωνηση πχ /vaccineStatusBloom 6991 Covid-19

Οι εντολες και τα ορισματα πρεπει να δωθουν ακριβως οπως εχουν
οριστει στην εκφωνηση καθως και στο inputfile.Σε διαφορετικη περιπτωση θα εκτυπωθει μηνυμα λαθους.

modules.h:Ορισμος κλασεων/structs/συναρτησεων αλλα και μικρες υλοποιησεις σε περιπτωσεις που δεν χρειαζετε πολυς κωδικας.

HashModule.cpp:σ

Για την υλοποιηση των hashtable εχει χρησιμοποιηθει κωδικας που ηταν γραμμενος σε c για παλαιοτερη εργασια 
στις δομες δεδομενων που χρησιμοποιει void * και οχι template εκτος απο την HTDelete και HTDestroy
που ηταν αναγκαιο, θα εξηγηθει παρακατω.
Η υλοποιηση των hashtable ειναι δυναμικη καθως οταν υπαρξουν 2 keys που εχουν το ιδιο hashkey(collision)επεκτεινετε η λιστα του 
key αυτου.Επισης οταν το loadfactor ξεπερασει το 0.9 τοτε το hashtable αυτοματα διπλασιαζει το μεγεθος του.
Δηλαδη θα μπορουσε να δωθει και size 1 και το προγραμμα θα συνεχισει να δουλευει κανονικα αυξανοντας λιγο τις δεσμευσεις και αποδεσμευσεις
καθως καθε διπλασιασμος δημιουργει εναν καινουργιο πινακα διπλου μεγεθους περνωντας τα παλια στοιχεια σε αυτον και διαγραφοντας τον παλιο.

ΗΤΙΤΕΜ = void*

int h(char* K,int TABLESIZE):Προκειτε για την HashFunction που δημηουργει HashKeys για καθε key που δινεται.

HTHash HTCreate(int size):Αρχικοποιει τον πινακα.

void Insertatstart(Hashnode *&list,std::string & key ,HTItem A):Εισαγει εναν κομβο στην λιστα του HashKey.

void NewTable(HTHash& table1):Κανει την διεργασια που περιγραφηκε παραπανω τον διπλασιασμο δηλαδη του πινακα οταν το Loadfactor >0.9.

void HTInsert(HTHash &table1,std::string & key,HTItem item):Εισαγει ενα στοιχειο στο hashtable.

int HTGet(HTHash table,std::string & key,HTItem* item):Ψαχνει αν το στοιχειο υπαρχει στο hashtable αν ναι επιστρεφει 1 διαφορετικα 0,στην πρωτη περιπτωση αντιγραφει
το αντοικειμενο του κομβου που βρηκε σε ενα void** που παιρνει για ορισμα .

int HTsearch(HTHash table,std::string & key):Το ιδιο αλλα χωρις την αντιγραφη του item.


modules.h:void Delete1(Hashnode **list, Hashnode *node) ΚΑΙ modulese.h:void HTRemove(HTHash table,std::string &key):
Ο λογος που αλλαξα τον κωδικα αυτων των δυο συναρτησεων και εβαλα templates ειναι διοτι οταν θελω να διαγραψω το στοιχειο
που ειναι αποθηκευμενο μεσα σε καποιον κομβο πρεπει να ξερω τι τυπου ειναι για να καλεσω τον καταληλο deconstructor και να διαγραφει οπως
πρεπει.Σε c υλοποιηση θα μπορουσα να κανω το ιδιο χρησιμοποιοντας ενα ορισμα που θα ηταν pointer σε συναρτηση για τον καθε φορα destructor η
καποια αλλη συναρτηση για deallocation αλλα η πρωτη επιλογη μου φανηκε ευκολοτερη.


module.h:class Bitarray:η κλαση αυτη ειναι η καρδια της υλοποιησης του bloomfilter καθως δημηουργει τον πινακα των bits και των επεξεργαζεται με μασκες και logical shifts.
Ο operator[] ειναι μια σχεδιαστικη επιλογη για το visualization δηλαδη να μοιαζει πως η ανακτηση μιας τιμης στο bitarray ειναι σαν ανακτηση σε εναν κανονικο
πινακα ενω στην πραγματικοτητα επιστρεφει το καταλlηλο bit με μασκα.
module.h:class Bloomfilter :υλοποιηση του bloomfilter μεσω ενως bitarray.

bloomfilter.cpp: Εδω υλοποιειτε η insert/lookup του bloomfilter για την εισαγωγη και αναζητηση στοιχειων σε αυτο.

module.h:class skiplist:Yλοποιηση της skiplist σαν εναν δισδιαστατο πινακα listnode.
skiplist.cpp:

int geth(int maxlevel):κανει την λειτουργια του "coinflip" και χρησιμοποιειτε για καθε στοιχειο που εισαγετε.

skiplist::skiplist(int mlevel):Αρχικοιποιηση της skiplist.

void skiplist::insert(int key,std::string& data):Εισαγωγη στοιχειου στην skiplist.
Για την εισαγωγη του στοιχειου αρχικα για καθε λεβελ εντοπιζετε μεσω καποιων while και if η θεση σε καθε υψος οπου θα πρεπει να μπει το στοιχειο,
και για καθε λεβελ που ειναι μικροτερο η ισο του coinflip στο σημειο αυτο που βρεθηκε εισαγετε ο pointer για το καινουργιο στοιχειο.Τελος στο μηδενικο 
λεβελ θα μπει και ο κομβος που θα περιεχει και τα στοιχεια που πρεπει να αποθηκευτουν στην περιπτωση μας ενα string που θα ειναι το Date. 

Οι υπολοιπες συναρτησεις δουλευουν με την ιδια λογικη εντοπιζαντας τις καταλληλες θεσεις και επεξεργαζοντας καταλληλα καθε φορα τα σημεια αυτα.

Ειδικη περιπτωση ειναι η int skiplist:: basesize_country που χρησιμοποιειτε για να βοηθησει στις εντολες που πρεπει να υπακουει το προγραμμα και επιστρεφει
τον αριθμο των vaccinated / notvaccinate ανθρωπων που βρισκονται σε καποιο συγκεκριμενο country .Η συναρτηση αυτη δεν επιτελει καποια λειτουργια για το
σκιπλιστ ειναι απλα βοηθητικη και θα μπορουσε να μην υπαρχει.

mainrelatedcpp:
bool is_number(const std::string& s):απανταει στο ερωτημα αν ενα string ειναι ψηφια και διασταβρωνει αν δωθηκε σωστο id.

int Date::setdate(std::string& date):μετατρεπΕΙ σε κλαση Date ενα στρινγκ που εχει το date που εχει δοθει αν επιτυχει επιστρεφει ενα αλλιως σημαινει πως 
δεν δΟθηκε καλος ορισμενο date και επιστρεφεται 0.

bool checkifbetweendates(Date &x,Date &y,Date &z):Eλεγχος για το αν ενα date ειναι μεταξυ δυο αλλων.¨

void printeveything(HTHash table,std::string &citizenID):Εκτυπωνει ολες τις καταστασεις των ιων για τους οποιους εχει υπαρχει εγγραφη με τον συγκεκριμενο 
citizen.

void print_country_statistics(HTHash filetable,Date date_1,Date date_2,std::string &secondelement,void*getv):
απαντα στην εντολη /populationStatus [country] virusName date1 date2.

void print_country_statistics_age(HTHash filetable,Date date_1,Date date_2,std::string &secondelement,void*getv):
απαντα στην εντολη /popStatusByAge [country] virusName date1 date2.

Οι συναρτησεις insert_record_file/user εισαγουν καταλληλα στις δομες τα records που δινονται απο αρχειο και απο user input αντιστοιχα.

void get_todays_date(std::string &date):επιστρεφει την σημερινη ημερομινια σαν string.

oid print_all_nonvaccinated(HTHash filetable,void * getvoid):
απαντα στην εντολη /list-nonVaccinated-Persons virusName.