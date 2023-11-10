#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct Day;

struct Card {
    Day* day;
    string front;
    string back;
    Card* next;
};

struct Day {
    int num;
    Card* head;
    Day* next;
};

void separator() {
    cout << "---------------" << endl;
}

void mergeDay(Day* day1, Day* day2) {
    day1->next = day2;
}

Day* createDay(int num) {
    Day* newDay = new Day;
    newDay->num = num;
    newDay->head = nullptr;
    newDay->next = nullptr;
    return newDay;
}

void create(Day* day, string frontText, string backText) {
    Card* current = day->head;
    Card* past = nullptr;
    while (current != nullptr) {
        past = current;
        current = current->next;
    }

    Card* newCard = new Card;
    newCard->day = day;
    newCard->front = frontText;
    newCard->back = backText;
    newCard->next = nullptr;

    if (day->head == nullptr) {
        day->head = newCard;
    } else {
        past->next = newCard;
    }

}

void pass(Card*& card) {
	if (card -> day -> num != 30){
	    Card* pastCardPastDay = card->day->head;
	    if (pastCardPastDay == card) {
	        card->day->head = card->next;
	    } else {
	        while (pastCardPastDay->next != card) {
	            pastCardPastDay = pastCardPastDay->next;
	        }
	        pastCardPastDay->next = card->next;
	    }
	    card->next = nullptr;
	
	    if (card->day->next != nullptr) {
	        card->day = card->day->next;
	        Card* pastCardNewDay = card->day->head;
	        if (pastCardNewDay != nullptr) {
	            while (pastCardNewDay->next != nullptr) {
	                pastCardNewDay = pastCardNewDay->next;
	            }
	            pastCardNewDay->next = card;
	        } else {
	            card->day->head = card;
	        }
	    } else {
	        Day* newDay = createDay(card->day->num + 1);
	        mergeDay(card->day, newDay);
	        card->day = newDay;
	        newDay->head = card;
	    }
	} else {
		Card* pastCard = card -> day -> head ;
		while(pastCard -> next != card ){
			pastCard = pastCard -> next ;
		}
		pastCard -> next = card -> next ;
		card -> next = NULL ;
		cout << "The card has successfully passed the thirty day period and has been deleted." ;
		delete card ;  	
	}
}

void refuse(Card* card, Day* day1) {
    string frontText = card->front;
    string backText = card->back;

    Card* current = day1->head;
    Card* past = nullptr;
    while (current != nullptr) {
        past = current;
        current = current->next;
    }

    Card* newCard = new Card;
    newCard->day = day1;
    newCard->front = frontText;
    newCard->back = backText;
    newCard->next = nullptr;

    if (day1->head == nullptr) {
        day1->head = newCard;
    } else {
        past->next = newCard;
    }

    if (card->day != day1) {
        Card* pastCard = nullptr;
        Card* currentCard = card->day->head;
        while (currentCard != card) {
            pastCard = currentCard;
            currentCard = currentCard->next;
        }
        if (pastCard != nullptr) {
            pastCard->next = card->next;
        } else {
            card->day->head = card->next;
        }
        card->day = day1;
        card->next = nullptr;
    }
}
void display(Day* day1 , int num) {
	int numCounter = 1 ;
	Day* day = day1 ;
	while (day -> num != num){
		day = day -> next ;
	}
	cout << "Day " << day -> num  << " : " << endl ;
    Card* current = day->head;
    while (current != NULL) {
        cout << current->front << "\t -> \t";
        cout << current->back << endl;
		separator() ;
        current = current->next;
    }
    cout << "***************" << endl << endl ;
    
}

void review(Day* startDay) {
	system("cls");
    Day* currentDay = startDay;
    while (currentDay != nullptr) {
    	cout << "\t \t \t \t \t \t -----------------            " << endl ;
        cout << "\t \t \t \t \t \t| Reviewing Day " << currentDay->num <<" |" << endl;
        cout << "\t \t \t \t \t \t -----------------" << endl ;
        Card* currentCard = currentDay->head;
        int count = 1;
        while (currentCard != nullptr) {
        	Card* tempCard = currentCard -> next ;
            cout << "Card " << count << ": \t " << currentCard->front << endl;
            char show  , response;
            cout << endl << endl <<endl <<endl <<endl <<endl <<endl <<"Enter 's' to display the answer and enter anything else to exit." ;
            cin >> show ;
            if (show == 's'){
            	system("cls");
            	cout << "\t \t \t \t \t \t -----------------            " << endl ;
			    cout << "\t \t \t \t \t \t| Reviewing Day " << currentDay->num <<" |" << endl;
			    cout << "\t \t \t \t \t \t -----------------" << endl ;
			    cout << "Card " << count << ": \t " << currentCard->front << endl;
            	cout << "answer : \t " << currentCard->back << endl;
			} else {
                return;
            }
            cout << endl << endl <<endl <<endl <<endl <<endl <<endl <<"Enter 'p' to pass, 'r' to refuse :";
            cin >> response;
            if (response == 'p') {
            	system("cls");
                pass(currentCard);
                count++;
            } else if (response == 'r') {
            	system("cls");
                refuse(currentCard, startDay );
                count++;
            } else {
                cout << "Invalid response. Please try again." << endl;
            }
            currentCard = tempCard ;
        }
        currentDay = currentDay->next;
    }
}

void info(){
	cout << "Commands guide : " << endl ;
	cout << "\tn = create new card" << endl ;
	cout << "\td = display cards of the day" << endl ;
	cout << "\tr = cards review" << endl ;
	cout << "\tc = clear terminal" << endl ;
	cout << "\te = exit" << endl ;
}

int main() {
	
	Day* pastDay = createDay(1);
	Day* day1 = pastDay ;
    Day* newDay = NULL ;
	for (int i = 2 ; i <= 30 ; i++){
		newDay = createDay(i);
		mergeDay(pastDay , newDay);
		pastDay = newDay ;
	}
	
	info();
	while (true){
		char menu ;
		cout << endl << "Enter command : " ;
		cin >> menu ;
		cin.ignore(); 
		cout << endl ;

		if (menu == 'e'){
			break ;
		} else if (menu == 'n'){
			separator() ;
	    	string frontText, backText;
		    cout << "Enter front text: ";
		    getline(cin, frontText); 
		    cout << "Enter back text: ";
		    getline(cin, backText); 
			create(day1 , frontText , backText );
		    cout << endl << "Card creation was successful!" << endl;
			separator();
			cout << endl;
		} else if (menu == 'd'){
			separator() ;
			int numDay ;
			cout << "Enter the day number : " ;
			cin >> numDay ;
			cout << endl ;
			display(day1 , numDay);
		} else if (menu == 'r'){
			review(day1);
			system("cls");
			info();
		} else if (menu == 'c'){
			system("cls");
			info();
		} else {
			cout << "Please enter the commands correctly!!" ;
		}	
		}
    return 0;
}

/*  
	Reza Asadi (Github : RezaGooner)
	1402/08/19 ~ 2023/11/10
*/
