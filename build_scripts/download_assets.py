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

file_url           = 'https://www.dropbox.com/scl/fi/hagxxndy0dnq7pu0ufkxh/assets.7z?rlkey=gmwlxlhf6q3eubh7r50q2xp27&st=60lavvyz&dl=1'
file_destination   = 'project/assets.7z'
file_expected_hash = '59cd3b52b0aa84ed3f9bfc9fdef7af945d3f42e134e8bc8bded2bc9519380b8a'

def main():
    file_utilities.download_file(file_url, file_destination, file_expected_hash)
    file_utilities.extract_archive(file_destination, "project/", True, True)

if __name__ == "__main__":
    main()