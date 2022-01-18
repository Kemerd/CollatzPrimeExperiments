// Copyright Donald Everett Hinton (2022)
// http://deveretthinton.net/
// https://www.linkedin.com/in/deveretthinton

// Includes 
#include <iostream>
#include <vector>
#include <stdlib.h>;

// Pre-definitions
void samurai();

// Multi-platform sleep fix
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x)\
Sleep(1000 * (x));
#endif

// STD namespace
using namespace std;

// Quick macro to error and restart, and a bad joke
#define INVALID()                                                                                               \
    cout << "Sorry, your input was invalid.\n";                                                                 \
    sleep(1);                                                                                                   \
    cout << "Program begging for it's life..\n";                                                                \
    sleep(2);                                                                                                   \
    cout << "Considering..\n";                                                                                  \
    sleep(3);                                                                                                   \
    samurai();                                                                                                  \
    if( (rand()%100) > 50 )                                                                                     \
    {                                                                                                           \
        cout << "Very well, you may live.. don't try to test me with weird inputs again.\n";                    \
        return program();                                                                                       \
    }                                                                                                           \
    else                                                                                                        \
    {                                                                                                           \
        cout << "Sorry kid..\n";                                                                                \
        return 0;                                                                                               \
    }                                                                                                           

// Collatz
int collatz( int i, int count )
{
    /*  There is a problem with the collatz conjecture.
    *   It is due to the fact that it is defined as such:
    *         { n/2     if n≡0 (mod 2)
    *   f(n)= { 
    *         { n+3     if n≡1 (mod 2)
    *   
    *   Well, why is this a problem? Because it is in modular
    *   arithmetic notation. There are many operations you
    *   cannot do to it because of that. However, there is a way
    *   to avoid having to use "if" statements, by integrating
    *   the "if" statement directly into how the function works.
    * 
    *   I have shorthanded this as "conditionals," and the concept
    *   is relatively straightforward.
    *
    *   Let the function p(n) be as follows:
    * 
    *   p(n) = [E(n) * x(n)] + [V(n) * y(n)]
    * 
    *   Let the following always be true:
    *   E(n) & V(n) will ALWAYS return either 0, or 1. 
    *   E(n) + V(n) will ALWAYS be equal to 1.
    *   
    *   How is the above relevant? Well, if you have a function
    *   in modular arithmatic notation, like this:
    * 
    *         { n/2     if n≡0 (mod 2)
    *   f(n)= {
    *         { n+3     if n≡1 (mod 2)
    *   
    *   You can construct your conditional in such a way that satisfies
    *   all of the above statements, thereby giving you a simplified,
    *   expanded form of your arithmetic, which can allow you to do
    *   all sorts of things.
    * 
    *   For instance, to expand the collatz conjecture.
    * 
    *   Let x(n) = n/2
    *   Let y(n) = 3n+1
    * 
    *   Now, to construct an E(n) and V(n) that satisfies the above requirements.
    * 
    *   Let E(n) = (n(mod2) + 1)(mod2)
    *   or         (n%2+1)%2
    *   
    *   Let V(n) = n(mod2)
    *   or         n%2
    * 
    *   You can test this for yourself, or create a mathematical proof,
    *   but E(n) and V(n) will only ever return 0 or 1, and adding them
    *   together will always equal one.
    * 
    *   Now, completely expanded, the collatz conjecture.
    *   c(n) = [ {(n(mod2) + 1)(mod2)} * {x/2} ] + [ {n(mod2)} * {3n+1} ]
    *   or   = [ {(n%2+1)%2} * {x/2} ] + [ {n%2} * {3n+1} ]
    *     
    *   Theoretically, if you can prove that f(n) is equivelant
    *   to c(n), and prove that c(n) will always reach 1 when
    *   compounded into itself as a sequence, then you could prove
    *   the collatz conjecture entirely. Having a simplified
    *   form of the equation allows you to do a whole new level
    *   of permutations, so the idea is that one day someone,
    *   perhaps me or you, would solve this.
    * 
    *   Anyways, with this simplified, the equation itself is almost nothing.
    *   Let's do it. 
    */

    // Print
    cout << i << ", ";

    // End program
    if (i == 1) { return count; }

    // Collatz
    i = (((i % 2 + 1) % 2)* (i/2) ) + ((i%2) * (3*i + 1));
    
    // Raw recursive func, be careful of infinite loops with large values of i
    count++;
    collatz(i, count);
}

// Euler's linear sieve
// O(n) time complexity
int linear_sieve( int input ) {

    // Setup arrays and definitions
    const int N = input;
    vector<int> lp(N + 1);
    vector<int> pr;

    // Loop through all, O(n) complexity
    for (int i = 2; i <= N; ++i)
    {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
            cout << i << ", ";
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }

    // Return the number of primes
    return pr.size();
}

// Starts with collatz
// Runs the stop time of collatz through a sieve
// Takes the number of primes found from sieve back into collatz
// Random experiment, no value at all intellectually
int both(int i, int count, int maxiterations)
{
    // Collatz
    int collatz_stoptime = collatz(i, 0);
    cout << "cz[" << i << "], ";
    if (collatz_stoptime == 0) {
        return count; // cant pass 0 into sieve
    }
    
    // Sieve
    int sieve_countprime = linear_sieve(collatz_stoptime);
    cout << "ls[" << i << "], ";
    if (sieve_countprime == 0) {
        return count;
    }

    // Make sure I don't kill my PC
    count++;
    if (count >= maxiterations - 1) {
        return count;
    }

    // We go agane
    both(sieve_countprime, count, maxiterations);
}

// Should try running a sieve on the highest number collatz ever reaches
// sieve_highest

// Should also try running both() back in on itself 

// Program so we can run it over and over
int program()
{
    // Take input
    string input;
    cout << "Please enter exit, or type: collatz, linear_sieve, both!\n";
    cin >> input;
    cout << endl;

    // Exit if need be
    if (input == "exit")
    {
        return 0; // exit
    }

    // If not, collect further input
    int numinput = 0;
    cout << "Please enter a valid integer above 0.\n";
    cin >> numinput;
    cout << endl;

    // Check validity of input
    if (numinput <= 0)
    {
        INVALID()
    }

    // Return result of func
    if (input == "collatz")
    {
        cout << "===========================================================\n";
        int result = collatz(numinput, 0);
        cout << "Stopping time: " << result << endl
             << "===========================================================\n"
             << "\n";
        return program(); // continue
    }
    else if (input == "linear_sieve")
    {
        cout << "===========================================================\n";
        int result = linear_sieve(numinput);
        cout << "Number of primes found: " << result << endl
             << "===========================================================\n"
             << "\n";
        return program(); // continue
    }
    else if (input == "both")
    {
        cout << "===========================================================\n";
        int result = both(numinput, 0, 99999999);
        cout << "Iterations: " << result << endl
            << "===========================================================\n"
            << "\n";
        return program(); // continue
    }
    else
    {
        // If they entered something incorrectly
        INVALID()
    }
}

// Main function
int main()
{
    int result = program();
    return result;
}

// Notes and Inspirations
// https://arxiv.org/pdf/1710.05687.pdf Paper I am mentioned in
// https://proofwiki.org/wiki/Limit_of_Modulo_Operation
// https://empslocal.ex.ac.uk/people/staff/mrwatkin/zeta/devlin.pdf
// https://cp-algorithms.com/algebra/prime-sieve-linear.html
// https://codeforces.com/blog/entry/54090
// https://en.wikipedia.org/wiki/Big_O_notation#Family_of_Bachmann.E2.80.93Landau_notations

// Random bad reference
void samurai() 
{
    cout << R"(
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWWWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXkddddodddkKNWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKd:'',:loo:;,;xxokNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKkd;...,:c::od:,,;;':odoooodoldOXWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMN0o:;,,,,;cllc,,lc:;.  .;;,,,,'. .':oONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMW0c';l:,:coodo:,'',cc'    ..';;,;;'....'l0WMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMW0c';c:cloc;:;,;:,.;l;. .. .;ool:;;,''..',cOWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMNkc;cc;cc;,;olclllc:l;...,;;;lol:,,,,,'.':l;cKMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMXo:,:olol;.;l:;dkkKKkd;''.',,',:;,;,.   ..';::kWMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMXo:lllodxx:,locxXMMMMMWKl;;,''';ldkOkdc..  ..,,cKMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMNd;;cooodko;:oxKWMMMMMMMWXOkocd00KWMMWN0l..';. .'xMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMNd,:c:lodko:lx0NMMMMMMMMMMMMNXNNNMMMMMMMNx;..:'.''oWMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMXo';kxol:::cokWMMMMMMMMMMMMMMMMMMWMMMMMMMM0l'.,.',.lNMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMWKd;,lOddo::ccoKWWWWMMMMMMWWWMMMMMMMMMMMMMMM0o,.. ',.:XMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMWkl:,:dkoddoxdcxXNXXKKXWMWWKkkKNMMMMMMMMMMMMMKc'...;;.lNMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMWXdll,,lkolxdokddOKKKXXK000KKKOdx0WMMMMMMMMMMMMK:',. ,;,kMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMWKxxkl.'dkcoKxol;:ol,;cdk0KOxxkO00XWMMMMMMMMMMMMKc',,.,ccOMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMWK0OKO:.,xx,dKd;.       .,cx00O0KNNXNWWWMMMMMWWMM0:',:;;clOMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMWKKK0Kx;,cxl;kO:.           'ldoxKNNXNNNNWMMNXKKKXO;.'cooocOMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMWKX000o;;loocxd.             .:ldkOOOxdoodxxddkO0OOc..:odkxkKK0KNXK0O0XXNWMMMMMMMMMMMMMMM
MMMMMMMMMMMMWKk0Occlcoklc;..            .lxOOxl;.      ..,oOkxl,,oOKX0O00OxxdoxO0KK0KNMMMMMMMMMMMMMM
MMMMMMMMMMMMNOddd::llk0l..;;.          .ck0Kd.            .,odo;;kkxxxKNOocoO0dc,,c0NKXWMMMMMMMMMMMM
MMMMMMMMMMMMNkldo'.cxOXx':oo:         .ckKWNd.  .     ...   .,;.....'cOOocckWWKk;. 'xXXXWMWWMMMMMMMM
MMMMMMMMMMMMXxxk:,.:O0Xo;dOOl.      .':kXWMW0l.   .... .... ......;ccc:c::cOWN0Od'  .;k0kdcxNMMMMMMM
MMMMMMMMMMMMXkd:'..cOO0ccKXXOoc:;;,cx0KXWMMW0d. ....... ...  .''...:l:clll:oxodxol,...:lcc;,l0WMMMMM
MMMMMMMMMMMMKdll'..oOOO;dNkxOOkkddxKNWWWMMMNx;'.....  .... .,;;c, .':cllolcll,,lc':oc,,cddl,.;0MMMMM
MMMMMMMMMMNOocdo:c:dxkkl0KolxOOkkOKKNNNWMWWKdcx0l,'.. ..,;::,';xo. .,looddlooccodolxo..oO0Kd::kWMMMM
MMMMMMMMWKxooddocccodk0KKl:ooxOxdOkxxddkkkkkkOKNWNNKxldkkOO:..,oo;,oOkccxOkl:coolk0d,.;k0NWKooKMMMMM
MMMMMMMMXkxoc::c;;oxxx0Xo';dkx:. .'...,::c:cxOkd0WMMWNKOdc;;:loooxO00x:.,okl',cxOd;. .'lOXXkc:OMMMMM
MMMMMMMWOlcc;,;:;:d0klxk. ,okx,.',,.    .. ..;:ckNWWXkodo:,;dxdoodKWKl..,coodOOd,  ... cK0dl''kMMMMM
MMMMMMMMKxkd:lkc.;x0Odkx.  .lOkO0KKOolc,....   ,xK0kocll:c:cxolccxXMNxcdkockNO,  ...  ;kXx;,..xWMMMM
MMMWWWMMKdododl,,,l0OoxO'   'o0XNKxxXXK0kxllol::xo;;:cdlcl:oOdc::xXMXO0NKOdlc,...'.  .dKXd,..:KMMMMM
XXXXXXKXXKOxo:''c:cO0cdXo.  .oOKWXd:::coxxolOWNOc...ldlcoo:d0kdl;dXMX00OOxxxool,::.  :0KXx,''dWMMMMM
KKXX0OKKKKkc;;':o::0XdxOdo:..;dOXXOololcxKOOK0l. ..,ok:'ll:d0OxOllKMNKOkkOkkkkl:xd.  ,OK0d,..kMMMMMM
OOxoldOO0Ko;c;;dd:lKXxdxdkXx. lklldooocoXWNKd' ,l' .oOl.:oldOOONXKWMMN000kO00x;lOd,..'ldl;'.'0MMMMMM
dooxxlldxx:ckdcxklxX0oxxdd0Nd..,:c::cc:lxxo:.':ld, .;do;dOollkNMMMMMMMX0X0xkOo',c,';cc;'....:KMMMMMM
xOKNKOOxlcd0NKkxdkO0OxxdxdkNNo...,...,,'....ckooxc,,,ll;oxc;:x0XWMMMMMMX0XOxd:;,. .cOKO:. ,okNMMMMMM
WMMMWNX0kx0XNNNKxk0ddO0OxloKMXo,',.     .:oxOkcdOddl;:c:cc::o0XKOOXWMMMMXKKxccOx;,;o0XK:  ,kOKWMMMMM
WWMMMWWNXxkNWWMMX0XKkOkkdokNNK000KOdddxxxk0Okl:kKkdl;.,c;:okOOxxxxkOOXWMMWN0llxkdxKOk0o. .:dd0WMMMMM
0O0NNKOkKkxXNWMMNKNWXK0xdkXXkdkO0WMMWXKK0doxxco00kkl;,;::x0OxdlcdkkxodKNMMMMX0kdxxk0xolldxOxdOKNMMMM
xxxxdodONXOO00KNXKXNNWWNKKNXdlddxXMWKOKNXKOdld0NOddc;;,cxkxxdooxkkxkkxxOKXNMMWNOdxOOkdOXXXXNNXXXNMMM
Kkolox0KXN0OOxdxkx0NWMMMMWWWx;:cxXNXKXWMMWWWXXNXKx:;,,:lodooxxkkkkxxdokXNXXXKXXKKXKXK0XWWMMMMXXKKWMM
NKKXWMWK0NX0Oxx0KO0WMMMMMMMMKl,cx0XNWMMMMMMWXXWXkxxc,:::ccoxkddkOkd:;cONWWWWK000KNNNXXWMMMWMMWXNKKWM
WWNK0xoldXXkx0XWWK0WMMMMMMMMM0c;oOXNWMMMMMMXKWWOlcoc:lddokOkdxkxo:,;okOkOOkO0kdO0K0kXXkc::lO00NMN0XM
;,'....'o0KxkWMMWXOKWMMMMMMMMWO;cdOWMMMMMMNKNMOlc;;;cxKXKKK0XNKOdccddododk0XXX0dk0OxKWo    lkkNWWK0N
:cldxxxkkxd;;OWMMWKk0NMMMMMMMMWkcoONMMMMMMKKWWOlc:c:o0XXWNXXXKXNNX0xoxXNWMMMMMNol00kkOo.   ,xxod0N00
xxdolc;,.... .dNMMX00OKWMMMMMMMXxdKMMMMMMW00XXo:cdOkO0ddOKNMMWXXXXkOKKXWMMMMWWW0xOK00Od;.,'.,'  ,0NO
;,,:lloxkkO0d'.;OWWXK0x0WMMMMMMMX0NMMMMMW0k0N0coK0kkKk. ..,cxKNXKkdKMWXKKXXXX0OXXOk0XKxl,'c,     cXK
OO0NWMMMMMMMWk' ;KMXXNKXWWWMMMMMMMMMMMMN0k0WMOokxcckWNd;'.  .cdOKxdNMMMKk0NWMXk0WWKKWNko' :l.    .kW
)";
    cout << endl;
}

// Fun fact, while creating this program, I have never gotten spared by rand(), I died every time.