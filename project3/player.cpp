#include"player.h"
#include"actor.h"
#include"stack.h"
#include"list.h"
#include"point.h"
#include"aquarium.h"

#include<iostream>

// 1. Player( ... )
//		Constructs and initializes the Player/Actor and its member variables
//		Remembers and discovers the starting point.
Player::Player(Aquarium* aquarium, Point p, std::string name, char sprite)
	:Actor(aquarium, p, name, sprite), m_brain(), m_discovered(){
	// Discover the starting point
	m_discovered.addToFront(p);
	m_brain.push(p);
}

// 2. stuck()
bool Player::stuck() const {
	return getState() == State::STUCK;
}

// 3. update() 
//		This function implements an algorithm to look through the maze
//      for places to move (STATE::LOOKING). update also handles moving the 
//		player as well, if there is an open undiscovered cell to move to the  
//		player just moves there.  However, there will be cases in which there 
//		are no open or undiscovered cells, at this point the player must 
//		backtrack (State::BACKTRACK) to a point that is adjacent to the next
//		point the player was planning to visit
//
//		Backtracking is challenging, save it for the very very very last thing.
//		Make sure the Looking aspect compiles and works first.
void Player::update() {
    
    if(m_brain.isEmpty()){setState(State::STUCK); return;}
    
    if (getState()==State::LOOKING){
        
        if(!m_brain.isEmpty()) setCurr(m_brain.peek());
        
        Point p  = getCurr();
        
        Point* w = new Point(p.getX()-1, p.getY());
        Point* e = new Point(p.getX()+1, p.getY());
        Point* n = new Point(p.getX(), p.getY()-1);
        Point* s = new Point(p.getX(), p.getY()+1);
        
        m_backTrack.push(p);
        
        m_brain.pop();
        
        if (p == getAquarium()->getEndPoint()){setState(State::FREEDOM); return;}
        
        if((!(getAquarium()->isCellOpen(*w))||_discovered(*w))&&(!(getAquarium()->isCellOpen(*e))||_discovered(*e))&&(!(getAquarium()->isCellOpen(*n))||_discovered(*n))&&(!(getAquarium()->isCellOpen(*s))||_discovered(*s))){
            if(!m_brain.isEmpty()){setState(State::BACKTRACK); return;}
        }
        
        if(getAquarium()->isCellOpen(*w)&&!_discovered(*w)){
            m_brain.push(*w);
            m_discovered.addToFront(*w);
        }
        if(getAquarium()->isCellOpen(*e)&&!_discovered(*e)){
            m_brain.push(*e);
            m_discovered.addToFront(*e);
        }
        if(getAquarium()->isCellOpen(*n)&&!_discovered(*n)){
            m_brain.push(*n);
            m_discovered.addToFront(*n);
        }
        if(getAquarium()->isCellOpen(*s)&&!_discovered(*s)){
            m_brain.push(*s);
            m_discovered.addToFront(*s);
        }
        
        delete w;
        delete e;
        delete s;
        delete n;
    }
    
    if(getState()==State::BACKTRACK){
        
        Point p  = getCurr();
        
        Point* w = new Point(p.getX()-1, p.getY());
        Point* e = new Point(p.getX()+1, p.getY());
        Point* n = new Point(p.getX(), p.getY()-1);
        Point* s = new Point(p.getX(), p.getY()+1);
        
        if(getAquarium()->isCellOpen(*w)&&(m_brain.peek() == *w)) {setState(State::LOOKING); return;}
        else if(getAquarium()->isCellOpen(*e)&&(m_brain.peek() == *e)) {setState(State::LOOKING); return;}
        else if(getAquarium()->isCellOpen(*n)&&(m_brain.peek() == *n)) {setState(State::LOOKING); return;}
        else if(getAquarium()->isCellOpen(*s)&&(m_brain.peek() == *s)) {setState(State::LOOKING); return;}
        
        m_backTrack.pop();
        setCurr(m_backTrack.peek());
        
        delete w;
        delete e;
        delete s;
        delete n;
        
    }
    
}

// 4. say()
//		Already Implemented, nothing to do here
void Player::say() {

	// Freedom supercedes being eaten
	if (getState() == State::FREEDOM) {
		std::cout << getName() << ": WEEEEEEEEEEEEEEE!";
		return;
	}

	// Being eaten supercedes being lost
	switch (getInteract()) {
	case Interact::ATTACK:
		std::cout << getName() << ": OUCH!";
		break;
	case Interact::GREET:
		break;
	case Interact::ALONE:
	default:
		switch (getState()) {
		case State::LOOKING:
			std::cout << getName() << ": Where's the exit?";
			break;
		case State::STUCK:
			std::cout << getName() << ": Oh no! I'm Trapped!";
			break;
		case State::BACKTRACK:
			std::cout << getName() << ": Argh, all walls or discovered, gotta backtrack...";
			break;
		default:
			break;
		}

		break;
	}
}

// _discovered
//		returns true if the item is in the list
bool Player::_discovered(Point p) {
	return (m_discovered.findItem(p) != -1);
}
