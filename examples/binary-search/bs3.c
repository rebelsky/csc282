/**
 * bs.c
 *   A simple binary search library.
 *
 * Authors:
 *   Marty Allen <allenmar2@grinnell.edu>
 *   1115 8th Ave, Box #3027
 *   Grinnell, IA 50112
 *
 *   Learned Watson <learned.watson@protonmail.com>
 *   https://moschata.net
 *   1115 8th Ave, Box #4721
 *   Grinnell, IA 50112
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "bs.h"
#include <stdio.h>

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

int
binary_search_ints (int v, int a[], int n)
{
  if (a == NULL){
    return -1;
  }
  if (n == 0){
    return -2;
  }

  int lb = 0; int ub = n; int mid;
  
  while(1){
    mid = (lb + ub)/2;

    if (a[mid] > v){
      if (ub == mid)
        return -1;
      ub = mid;
    } else if (a[mid] < v) {
      if (lb == mid)
        return -1;
      lb = mid;
    } else {
      if (a[mid] == v){
        return mid;
      }
      return -1;
    }

  }

} // binary_search_ints

/*

Copyright (C) 2021 Learned Watson, Marty Allen

Pursuant to Grinnell College policy, students and faculty retain the
copyright to any works ,,[they create] in the course of their normal ac-
ademic pursuits.''

This and any other such works distributed herewith are subject to the exclusive copyleft of the authors.

They may be reproduced, readapted, reconveyed, retransmitted, rewritten,
released, and reimagined,
in whole or in part,
with or without attribution,
by anyone for any purpose whatever,
provided derived works are distributed under this license.
The only other restriction
is that the reuser
please recycle.

THE SOFTWARE IS PROVIDED ``AS IS,'' WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

