#ifndef FORWARDLIST_H
#define FORWARDLIST_H
typedef int Item;
namespace Flist
{
    struct node
    {
        Item key;
        node *next;
        node(Item k, node *n){key = k; next = n;}
    };
    typedef node *link;
    link h = nullptr;

    void addBef(Item bef, Item ad)
    {
        if (h == nullptr)
            return;
        else
        {
            if (h->key == bef)
            {
                link a = new node(ad, nullptr);
                a->next = h;
                h = a;
                return;
            }
            link t = h;
            while (t->next != nullptr)
            {
                if (t->next->key == bef)
                {
                    link a = new node(ad, nullptr);
                    a->next = t->next;
                    t->next = a;
                    break;
                }
                t = t->next;
            }
        }
    }
    void addAft(Item aft, Item ad)
    {
        if (h == nullptr)
            return;
        else
        {
            link t = h;
            while (t != nullptr)
            {
                if (t->key == aft)
                {
                    link a = new node(ad, nullptr);
                    a->next = t->next;
                    t->next = a;
                    break;
                }
                t = t->next;
            }
        }
    }
    void addSta(Item nw)
    {
        if (h == nullptr)
            h = new node(nw, nullptr);
        else
        {
            link t = new node(nw, nullptr);
            t->next = h;
            h = t;
        }
    }
    void addEnd(Item nw)
    {
        if (h == nullptr)
            h = new node(nw, nullptr);
        else
        {
            link t = h;
            while (t->next != nullptr)
                t = t->next;
            link temp = new node(nw, nullptr);
            t->next = temp;
        }
    }
    void printList(link ha = h)
    {
        if (ha == nullptr)
            return;
        link t = ha;
        while (t != nullptr)
        {
            std::cout << t->key << " ";
            t = t->next;
        }
        std::cout << std::endl;
    }
    void del(Item d)
    {
        if (h == nullptr)
            return;
        else
        {
            if (h->key == d)
            {
                link temp = h->next;
                delete h;
                h = temp;
                return;
            }
            link t = h;
            while (t != nullptr)
            {
                if (t->next->key == d)
                {
                    link temp = t->next;
                    t->next = t->next->next;
                    delete temp;
                    break;
                }
                t = t->next;
            }
        }
    }
    void delBef(Item bef)
    {
        if (h == nullptr)
            return;
        else
        {
            if (h->key == bef)
            {
                return;
            }
            else if (h->next->key == bef)
            {
                link temp = h->next;
                delete h;
                h = temp;
                return;
            }
            link t = h;
            while (t->next->next != nullptr)
            {
                if (t->next->next->key == bef)
                {
                    link temp = t->next;
                    t->next = t->next->next;
                    delete temp;
                    break;
                }
                t = t->next;
            }
        }
    }
    void delAft(Item aft)
    {
        if (h == nullptr)
            return;
        else
        {
            if (h->key == aft && h->next != nullptr)
            {
                link temp = h->next;
                h->next = h->next->next;
                delete temp;
                return;
            }

            link t = h;
            while (t->next != nullptr)
            {
                if (t->key == aft)
                {
                    link temp = t->next;
                    t->next = t->next->next;
                    delete temp;
                    break;
                }
                t = t->next;
            }
        }
    }
    void delSta()
    {
        if (h == nullptr)
            return;
        else
        {
            link temp = h->next;
            delete h;
            h = temp;
        }
    }
    void delEnd()
    {
        if (h == nullptr)
            return;
        else
        {
            link t = h;
            while (t->next->next != nullptr)
                t = t->next;
            link temp = t->next;
            t->next = t->next->next;
        }
    }
    bool search(Item s)
    {
        if (h == nullptr)
            return 0;
        else
        {
            bool check = false;
            link t = h;
            while (t != nullptr)
            {
                if (t->key == s)
                {
                    check = true;
                    break;
                }
                t = t->next;
            }
            return check;
        }
    }
}
#endif