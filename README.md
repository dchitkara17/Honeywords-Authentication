# Honeywords-Authentication
 We aim to explore the efficacy of honeywords-based authentication systems in countering online password-guessing algorithms.

 I have used the COMB dataset which can be Downloaded from `https://downloadtorrentfile.com/hash/af2879db0fab2a32ba38d0491aa8fea5e29d3678?name=CompilationOfManyBreaches.7z`

 The make_data file takes the input file as the path of the data directory of the COMB dataset downlaoded above.
  Run the command
 `g++ make_data.cpp -o data && ./data`

 Then run 
 `g++ testing.cpp -o testing && ./testing` and enter the file name in the above command.

You will get the result of the number of passwords cracked for the file.
