class IOption {
   public:
        virtual void printOption();
        virtual void switchOption();

        int maxLvl;
        int currentLvl;
        int optionNumbers;
};

class FreeRoam : public IOption {
    public:
        void printOption(){};
        void switchOption(){};

        int maxLvl = 1;
        int currentLvl = 1;
        int optionNumbers = 0;
};