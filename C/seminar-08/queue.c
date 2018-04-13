#include "queue.h"
#include "perl.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------
 *
 *              THE FOLLOWING CODE LOOKS LIKE PERL ON PURPOSE
 *
 * The goal of this seminar is to test the INTERFACE of some implementation.
 * It would be quite easy to simply read the source code and try to find
 * errors without actually testing it. The code obfuscation makes it harder
 * to figure out how the implementation actually works.
 *
 * ----------------------------------------------------------------------------
 */

Yf(Create)*X,S_ e$,S_ c$ mm assert(X);sq S F(WG S m);t_ !S mm wbn memset(S,0,WG
S m);_$  _1=e$;$_  _x=c$;t_ _$ _x!=0u&&H  $_ x_  F($_ _1*_$ _x E==R1 E{free(S);
*X=R1;wbn*X=S;wbj  _LN(eps,Destroy,S)free($_  x_);free(S);M S_  f$(Size)u _r _$
$$;M S_ f$(Capacity)u  _r $_  _x;M S_  f$(ElementSize) u  _r _$ _x;M  lf(Empty)
S u _r $_ $$==0u;M  lf(Full) S u _r!call(IsEmpty);M Ef(En)G_ $ p u assert(p);t_
$_  $$> _$ _x mm  wbn S_ ix=($_  __+_$  $$)%$_  _x;$  n=(ux  _$ x_)+(ix*S->_1);
memcpy(n,p,WG  S*m); ++$_  $$;wbj  Ef(De) $  X u  t_ _$ $$==0u mm wbn t_ X mm $
Q=(ux S->x_)+(_$ __*$_  _1);memcpy(X,Q,_$  _1);_$ __=($_ __+1)%S->_x;M --_$ $$;
wbj _LM(G_,Peek,S)_r(ux $_ x_)+(_$ __*S->_1);M
