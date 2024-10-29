#Copyright(c) 2016-2024 Panos Karabelas
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
#copies of the Software, and to permit persons to whom the Software is furnished
#to do so, subject to the following conditions :
#
#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
#FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
#COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
#IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
#CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import file_utilities

file_url           = 'https://www.dropbox.com/scl/fi/xkc76vrsiwu4l2f67030e/assets.7z?rlkey=r3kym37skmay9e79slre6e60j&st=0jn5etfu&dl=1'
file_destination   = 'project/assets.7z'
file_expected_hash = 'e57b718a109a5fa94561d894cb67d33535754ad6926ab99f53ce457a751e90ac'

def main():
    file_utilities.download_file(file_url, file_destination, file_expected_hash)
    file_utilities.extract_archive(file_destination, "project/", True, True)

if __name__ == "__main__":
    main()