class GameWorld {
    private:
    
    public:
        void keyPressed(sf::Event keyEvent);
        void keyReleased(sf::Event keyEvent);
        void mousePressed(sf::Event mouseEvent);
        void mouseReleased(sf::Event mosueEvent);
        
};

void GameWorld::keyPressed(Keyboard::Key keyEvent){
    if(keyEvent == 'A')
        cout << "bokstaven a var nedtryckt" << endl;
}

void GameWorld::keyReleased(Keyboard::Key keyEvent){
    if(keyEvent == 'A')
        cout << "bokstaven a var släppt" << endl; 
}

void GameWorld::mousePressed(Mouse::Button mouseEvent){
    
}

void GameWorld::mouseReleased(Mouse::Button mosueEvent){
    
}


