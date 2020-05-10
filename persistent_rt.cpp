#include <iostream>
#include <vector>

using namespace std;


struct node {
    node *lc, *rc;
    const int l, r;
    int sum;

    node(int L, int R): l(L), r(R), sum(0) {
        if(!leaf()) {
            int mid = (L+R)/2;
            lc = new node(L, mid);
            rc = new node(mid+1, R);
        } else {
            lc = NULL;
            rc = NULL;
        }
    };

    bool leaf() const {
        return l == r;
    }

    node(const node& n): l(n.l), r(n.r), lc(n.lc), rc(n.rc), sum(n.sum) {}

    int query(int ql, int qr) {
        cerr << "Query at " << l << " " << r << ": " << sum << "\n";
        if(qr < l || r < ql) {
            return 0;
        } else if(ql <= l && r <= qr) {
            return sum;
        } else {
            return lc->query(ql, qr) + rc->query(ql, qr);
        }
    }

    node* update(int pos, int d) {
        cerr << "At node " << l << " " << r << "\n";
        if(pos < l || r < pos) {
            return this;
        }
        node* newnode = new node(*this);
        if(!leaf()) {
            newnode->lc = lc->update(pos, d);
            newnode->rc = rc->update(pos, d);
            newnode->calc();
        } else {
            newnode->sum += d;
        }
        return newnode;
    }

    void calc() {
        if(!leaf()) sum = lc->sum + rc->sum;
    }

};

int main() {
    int N;
    cin >> N;
    vector<node*> rt{new node(1, N)};
    while(1) {
        char op;
        int a1, a2, a3;
        cin >> op;
        cin >> a1 >> a2;
        if(op == 'U') {
            cerr << "Doing an update\n";
            rt.push_back(rt[rt.size()-1]->update(a1, a2));
        } else {
            cin >> a3;
            cerr << op << a1 << a2 << "\n";
            cout << "Sum of elements from " << a2 << " to " << a3 << " at time " << a1 << " is: " << rt[a1]->query(a2, a3) << "\n";
        }
    }
}
