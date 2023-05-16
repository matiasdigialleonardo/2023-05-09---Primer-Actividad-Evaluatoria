#include <iostream>
#include <vector>
#include <algorithm>

class IListable
{
    public:
        virtual ~IListable(){};
        virtual void list(int depth) = 0;
};

class IComposableOfListable
{
    public:
        virtual ~IComposableOfListable(){};
        virtual void add(IListable* component) = 0;
        virtual void remove(IListable* component) = 0;
};

class Library : public IListable, IComposableOfListable
{
    public:
        virtual ~Library(){};
        virtual void list(int depth) = 0;
        virtual void add(IListable* component) = 0;
        virtual void remove(IListable* component) = 0;
};


class SoundTrack : public Library
{
    private:
        std::string m_nodeName;
        std::vector<IListable*> m_listOfChildren;

    public:
        SoundTrack(std::string nodeName)
        {
            m_nodeName = nodeName;
        }

        virtual ~SoundTrack(){}
        
        void list(int depth)//operation
        {
            std::string newStr(depth, '-');
            std::cout << newStr << m_nodeName << " depth: " << depth << std::endl;

            for(IListable* currentChild : m_listOfChildren)
            {
                if(currentChild != 0)
                {
                    currentChild->list(depth + 1);
                }
            }
        }

        void add(IListable* component)
        {
            m_listOfChildren.push_back(component);
        }

        void remove(IListable* component)
        {
            m_listOfChildren.erase(std::remove(m_listOfChildren.begin(), m_listOfChildren.end(), component), m_listOfChildren.end());
        }
};

class Films : public Library
{
    private:
        std::string m_nodeName;
        std::vector<IListable*> m_listOfChildren;

    public:
        Films(std::string nodeName)
        {
            m_nodeName = nodeName;
        }

        virtual ~Films(){}
        
        void list(int depth)//operation
        {
            std::string newStr(depth, '-');
            std::cout << newStr << m_nodeName << " depth: " << depth << std::endl;

            for(IListable* currentChild : m_listOfChildren)
            {
                if(currentChild != 0)
                {
                    currentChild->list(depth + 1);
                }
            }
        }

        void add(IListable* component)
        {
            m_listOfChildren.push_back(component);
        }

        void remove(IListable* component)
        {
            m_listOfChildren.erase(std::remove(m_listOfChildren.begin(), m_listOfChildren.end(), component), m_listOfChildren.end());
        }
};

class VideoMedia : public IListable
{
    private:
        std::string m_nodeName;

    public:
        VideoMedia(std::string nodeName)
        {
            m_nodeName = nodeName;
        }

        virtual ~VideoMedia(){}

        void list(int depth)//operation
        {
            std::string newStr(depth, '-');
            std::cout << newStr << m_nodeName << " depth: " << depth << std::endl;
        }
};

class AudioMedia : public IListable
{
    private:
        std::string m_nodeName;

    public:
        AudioMedia(std::string nodeName)
        {
            m_nodeName = nodeName;
        }

        virtual ~AudioMedia(){}

        void list(int depth)//operation
        {
            std::string newStr(depth, '-');
            std::cout << newStr << m_nodeName << " depth: " << depth << std::endl;
        }
};


int main()
{
    Library* soundTracks = new SoundTrack("Mili");

    Library* toKillALivingBook = new SoundTrack("To Kill a Living Book");
    toKillALivingBook->add(new AudioMedia("String Theocracy"));
    toKillALivingBook->add(new AudioMedia("Iron Lotus"));

    soundTracks->add(toKillALivingBook);
    
    soundTracks->list(1);




    return 0;
}