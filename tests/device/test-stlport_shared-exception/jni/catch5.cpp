// { dg-do run  }
// { dg-options "-w" }
// Copyright (C) 1999, 2000 Free Software Foundation, Inc.
// Contributed by Nathan Sidwell 29 Aug 1999 <nathan@acm.org>

// We cannot catch an ambiguous base class.
// -- public, << private, == virtual

// D--B==A
// +--C==A
// +--AA-A


struct A { int m; };
struct B : virtual A { int m; };
struct C : virtual A { int m; };
struct AA : A { int m; };
struct D : B, C, AA { int m; };

void fna(A *obj) { throw obj; }
void fnb(B *obj) { throw obj; }
void fnc(C *obj) { throw obj; }
void fnd(D *obj) { throw obj; }
void fnaa(AA *obj) { throw obj; }

extern "C" void abort();

void check(D *d)
{
  int caught;
  
  // try with whole object
  caught = 0;
  try { fnd(d); }
  catch(A *p) { abort(); } // A is ambiguous
  catch(D *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();

  caught = 0;
  try { fnd(d); }
  catch(A *p) { abort(); } // A is ambiguous
  catch(B *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();

  caught = 0;
  try { fnd(d); }
  catch(A *p) { abort(); } // A is ambiguous
  catch(C *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();

  caught = 0;
  try { fnd(d); }
  catch(A *p) { abort(); } // A is ambiguous
  catch(AA *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();

  // try with an A object
  caught = 0;
  try { fna((B *)d); }
  catch(B *p) { abort(); } // throw type is static type
  catch(A *p) { caught = 1; if (p != (B *)d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fna((C *)d); }
  catch(C *p) { abort(); } // throw type is static type
  catch(A *p) { caught = 1; if (p != (C *)d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fna((AA *)d); }
  catch(AA *p) { abort(); } // throw type is static type
  catch(A *p) { caught = 1; if (p != (AA *)d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  // try with B object
  caught = 0;
  try { fnb((B *)d); }
  catch(A *p) { caught = 1; if (p != (B *)d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fnb((B *)d); }
  catch(B *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fnb((B *)d); }
  catch(C *p) { abort(); }
  catch(D *p) { abort(); }
  catch(...) { caught =1; }
  if (!caught) abort();
  
  // try with C object
  caught = 0;
  try { fnc((C *)d); }
  catch(A *p) { caught = 1; if (p != (C *)d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fnc((C *)d); }
  catch(C *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fnc((C *)d); }
  catch(B *p) { abort(); }
  catch(D *p) { abort(); }
  catch(...) { caught =1; }
  if (!caught) abort();
  
  // try with AA object
  caught = 0;
  try { fnaa((AA *)d); }
  catch(A *p) { caught = 1; if (p != (AA *)d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fnaa((AA *)d); }
  catch(AA *p) { caught = 1; if (p != d) abort();}
  catch(...) { abort(); }
  if (!caught) abort();
  
  caught = 0;
  try { fnaa((AA *)d); }
  catch(C *p) { abort(); }
  catch(B *p) { abort(); }
  catch(D *p) { abort(); }
  catch(...) { caught =1; }
  if (!caught) abort();
  
  return;
}

int main ()
{
  D d;
  check (&d); // try with an object
  check ((D *)0); // try with no object
  
  return 0;
}
