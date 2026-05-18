#include <iostream> 
#include <vector>   
#include <string>   

using namespace std;

class Event {
protected:
    string title;
    string date;

public:
    Event() : title("TBD"), date("01.01.2026") {}

    Event(string t, string d = "Today") : title(t), date(d) {}

    virtual ~Event() {}

    virtual void printInfo() const {
        cout << "Event: " << title << " | Date: " << date;
    }

    void postpone(string newDate) { date = newDate; }

    void cancel() { title = "[CANCELLED] " + title; }
};

class PrivateEvent : public Event {
protected:
    int guestCount;
    bool isInviteOnly;

public:
    PrivateEvent() : Event(), guestCount(0), isInviteOnly(true) {}

    PrivateEvent(string t, string d, int guests, bool invite = true)
        : Event(t, d), guestCount(guests), isInviteOnly(invite) {
    }

    void printInfo() const override {
        Event::printInfo();
        cout << " | Private | Guests: " << guestCount;
    }

    void updateGuestList(int newCount) { guestCount = newCount; }

    void sendInvites() const { cout << " -> Invites sent!" << endl; }
};

class PublicEvent : public Event {
protected:
    double ticketPrice;
    string location;
    double money;

public:
    PublicEvent() : Event(), ticketPrice(0.0), location("Online"), money(0.0) {}

    PublicEvent(string t, string d, string loc, double price, double m)
        : Event(t, d), location(loc), ticketPrice(price), money(m) {
    }

    void printInfo() const override {
        Event::printInfo();
        cout << " | Public | Location: " << location
            << " | Price: " << ticketPrice << " lv."
            << " | Money: " << money << " lv.";
    }

    void sellTicket() { cout << " -> Ticket sold!" << endl; }

    void announce() const { cout << " -> Announcement made!" << endl; }
};

class CharityEvent : public Event {
protected:
    string cause;
    double raisedAmount;

public:
    CharityEvent() : Event(), cause("General"), raisedAmount(0.0) {}

    CharityEvent(string t, string d, string c, double r = 0.0)
        : Event(t, d), cause(c), raisedAmount(r) {
    }

    void printInfo() const override {
        Event::printInfo();
        cout << " | Charity | Cause: " << cause << " | Raised: " << raisedAmount << " lv.";
    }

    void donate(double amount) { raisedAmount += amount; }

    void showImpact() const { cout << " -> Helping for: " << cause << endl; }
};

class Wedding : public PrivateEvent {
    string coupleNames;
    bool hasLiveMusic;

public:
    Wedding() : PrivateEvent(), coupleNames("TBD"), hasLiveMusic(false) {}

    Wedding(string d, int guests, string names, bool music = true)
        : PrivateEvent("Wedding", d, guests, true), coupleNames(names), hasLiveMusic(music) {
    }

    void printInfo() const override {
        PrivateEvent::printInfo();
        cout << " | Couple: " << coupleNames << endl;
    }

    void toast() const { cout << " -> Cheers for " << coupleNames << "!" << endl; }

    void cutCake() const { cout << " -> Cutting the cake!" << endl; }
};

class Concert : public PublicEvent {
    string performer;
    int durationMinutes;

public:
    Concert() : PublicEvent(), performer("Artist"), durationMinutes(90) {}

    Concert(string t, string d, string loc, string perf, int dur = 120)
        : PublicEvent(t, d, loc, 50.0, 1000.0), performer(perf), durationMinutes(dur) {
    }

    void printInfo() const override {
        PublicEvent::printInfo();
        cout << " | Artist: " << performer << " | Dur: " << durationMinutes << "min" << endl;
    }

    void startShow() const { cout << " -> Show starts!" << endl; }

    void encore() const { cout << " -> One more song!" << endl; }
};

class Birthday : public PrivateEvent {
    int age;
    string giftIdea;

public:
    Birthday() : PrivateEvent(), age(1), giftIdea("None") {}

    Birthday(string t, string d, int guests, int a, string gift = "Surprise")
        : PrivateEvent(t, d, guests, true), age(a), giftIdea(gift) {
    }

    void printInfo() const override {
        PrivateEvent::printInfo();
        cout << " | Age: " << age << " | Gift: " << giftIdea << endl;
    }

    void blowCandles() const { cout << " -> Blowing " << age << " candles!" << endl; }

    void openGifts() const { cout << " -> Opening " << giftIdea << "!" << endl; }
};

int main() {
    vector<Event*> calendar;

    calendar.push_back(new Wedding("20.06.2026", 120, "Ani & Mark"));
    calendar.push_back(new Concert("Rock Night", "15.07.2026", "Stadium", "Arctic Monkeys"));
    calendar.push_back(new CharityEvent("Save the Forest", "10.10.2026", "Ecology", 500.0));
    calendar.push_back(new Birthday("Ani's B-Day", "13.05.2026", 20, 22, "Laptop"));

    cout << "--- EVENT LIST ---" << endl;

    for (Event* e : calendar) {
        e->printInfo();

        if (Wedding* w = dynamic_cast<Wedding*>(e))
            w->toast();

        else if (Concert* c = dynamic_cast<Concert*>(e))
            c->startShow();

        else if (CharityEvent* ch = dynamic_cast<CharityEvent*>(e))
            ch->showImpact();

        else if (Birthday* b = dynamic_cast<Birthday*>(e))
            b->blowCandles();

        cout << "------------------" << endl;
    }

    for (Event* e : calendar)
        delete e;

    return 0;
}