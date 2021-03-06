/* Template argument tests.

   Copyright 2010 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Please email any bugs, comments, and/or additions to this file to:
   bug-gdb@gnu.org  */

int a_global;

struct S
{
  int f;
};

template<typename T, int I, int *P, int S::*MP>
struct Base
{
  template<typename Z>
  struct Inner
  {
    void inner_m ()
    {
      // Breakpoint 2.
    }
  };

  void base_m ()
  {
    // Breakpoint 1.
  }

  template<typename Q>
  void templ_m ()
  {
    // Breakpoint 4.
  }
};

template<typename T, int I, int *P, int S::*MP>
void func ()
{
  // Breakpoint 3.
}

int main ()
{
  Base<double, 23, &a_global, &S::f> base;
  // Note that instantiating with P==0 does not work with g++.
  // That would be worth testing, once g++ is fixed.
  Base<long, 47, &a_global, &S::f>::Inner<float> inner;

  base.base_m ();
  inner.inner_m ();
  func<unsigned char, 91, &a_global, &S::f> ();
  base.templ_m<short> ();

  return 0;
}
