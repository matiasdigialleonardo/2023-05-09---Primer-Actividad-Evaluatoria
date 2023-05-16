/**
    Project     : Composite Pattern Example

    Authors     : Erich Gamma, Richard Helm, Ralph Johnson and John Vlissides
**/

///////////////////////////////////////////ICOMPONENT-INTERFACE///////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>

class IListable
{
    public:
        virtual ~IListable(){};
        virtual void list(int depth) = 0; //operation
};

class IComposableOfListable
{
    public:
        virtual ~IComposableOfListable(){};
        virtual void add(IListable* component) = 0;
        virtual void remove(IListable* component) = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////COMPOSITE///////////////////////////////////////////////////////
class Folder : public IListable, public IComposableOfListable
{
    private:
        std::string m_nodeName;
        std::vector<IListable*> m_listOfChildren;

    public:
        Folder(std::string nodeName)
        {
            m_nodeName = nodeName;
        }

        virtual ~Folder(){}
        
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////LEAF////////////////////////////////////////////////////////
class File : public IListable
{
    private:
        std::string m_nodeName;

    public:
        File(std::string nodeName)
        {
            m_nodeName = nodeName;
        }

        virtual ~File(){}

        void list(int depth)//operation
        {
            std::string newStr(depth, '-');
            std::cout << newStr << m_nodeName << " depth: " << depth << std::endl;
        }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////
int main()
{
    Folder* folder_01 = new Folder("folder_01");

    Folder* folder_02 = new Folder("folder_02");
    folder_01->add(folder_02);

    Folder* folder_03 = new Folder("folder_03");
    folder_03->add(new File("file A"));
    folder_03->add(new File("file B"));
    folder_02->add(folder_03);
    
    folder_01->list(1);

    delete folder_03;
    delete folder_02;
    delete folder_01;
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////