

 # SPARSE_MATRIX_OPERATIONS
 # This project presents the implementation of basic sparse matrix operations.
 #
 # Copyright (C) 2024, Rico Morasata.
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <https://www.gnu.org/licenses/>.
 #
 # DISCLAIMER OF LIABILITY
 #
 # THIS SOFTWARE IS PROVIDED BY RICO MORASATA "AS IS" AND ANY
 # EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 # WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 # DISCLAIMED. IN NO EVENT SHALL RICO MORASATA BE LIABLE FOR ANY
 # DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 # (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 # LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 # ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 # (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 # SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 


cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 99 CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2")

set(EXECUTABLE_OUTPUT_PATH ./bin)

project(main LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/headers)


file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/sources/#.c)

add_executable(main ${SOURCES})


