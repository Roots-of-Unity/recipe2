## recipe2 ##
a command line tool for recipes and shopping lists
#### Introduction ####
why I switched to the store schema idea
Also, why GRM won't work for every shopping scenario and why more utilities must exist. (think sublists, multiple stores, and mucinex)
#### Description of Problem ####
write me.
#### Proposed Solution ####
write me.
#### Shopping List Ordering Algorithm ####
description.
#### Example Toolchain Scenario ####
Example: I want to prepare a weeks worth of freezer meals for my family. So I begin by generating a shopping list using [Gourmet Recipe Manager](https://github.com/thinkle/gourmet). I want to make one of every dish in my database and 2 slow cooker green bean sides:

![](http://i.imgur.com/vnxz9eB.png)

So I generate a shopping list:

![](http://i.imgur.com/H1CchIB.png)

and format it slightly and print it: (future developments might include using Gourmet Recipe Manager's sqlite database directly)

![](http://i.imgur.com/cy8Tnv1.jpg)

Now that the list is printed firmly onto the original computational device: paper; I can proceed and order it according to the Shopping List Ordering Algorithm described in detail on the wiki. **PUT A LINK HERE**.

![](http://i.imgur.com/t9PFZVz.jpg)

Now, while that list is now "ordered" (future developments include a mobile app to perform this ordering. It's easier graphically and with touch.) in the sense that I've extracted the information that my head knows about 86th Street Costco inventory sequence, it won't be helping anyone in its present form. The list needs to be organized from least to greatest according to the penciled in sequence numbers.

To do that, (and this is why a graphically and touch based app would be the best interface here) I'm going to turn that boring task over to my program. But first, I need to prepare a file that can be read by my project.

I quickly copy and paste the list I printed out into a column in a spreadsheet.

![](http://i.imgur.com/Lv02fYZ.png)

Then I visually parse the hand-sequenced shopping list into the spreadsheet. This is easy because the items are in the same order in both paper and spreadsheet.

![](http://i.imgur.com/c65fG5j.png)

Now, the magic can happen! Observers may note that You can sort the spreadsheet and generate an ordered list, however, it would be challenging to store an overall "schema" about a particular shopping-store using this method. My project takes the first steps into fully implementing store  sequence schemas.

Next, export the spreadsheet as a a UTF-8 encoded, comma separated values file (*.csv):

![](http://i.imgur.com/joN7CSD.png)

For added compatibility (un-necessary on the system I tested with): Use a full-featured text editor (like Notepad++ on Windows) to make sure that the file is UTF-8 without BOM (That's byte order mark. It denotes which UTF encoding the file is in. There are several UTF encodings. The BOM could potentially cause issues.) And make sure that the line ending EOL character matches the target system. I tested with both and the project ran fine.

Next, put your single or multiple shopping list files... (that are ordered as a single sequence. For example: multiple sequences through a store would be lists you made for different trips to the store on different days. Taken together, these lists would not be a single sequence. Ordering these into one schema about a store: say 86th Street Costco is where I have an algorithm developed **SEE WIKI LINK HERE**, and will be implemented in later sessions. The part I coded for this session will be necessary to implement this further down the road.) 

An example of multiple lists that are put in the same sequence using the power of decimal numbers. This grocery list is an old relic that was ran with a typical color coding method: 

![](http://i.imgur.com/k45U5ei.jpg)

The above lists have been included as test *.csv files in the /tests/data directory of this project.

Next...put your single or multiple shopping list files that are in a single sequence into the **same directory** (filesystems are OS specific... therefore I glanced over this feature) as the recipe2 executable, and run the program as follows (assuming Windows in example):

![](http://i.imgur.com/MLwD5QL.png)

And the organized result should be:

![](http://i.imgur.com/gtTTyK6.png)

You can save this output by using your OS's redirection operators (Windows docs found [here](https://technet.microsoft.com/en-us/library/bb490982.aspx).) And copy and paste this into a word processor for a nice organized, and printable list.

![](http://i.imgur.com/pwSUSwM.png)

And then you can get really meta by running that output.txt through the program again. (Only joking, eventually it will be possible, and useful to do that.)

#### Next Steps ####
#### Future Developments ####
## Documentation

## Credits and Thanks ##
Playlists  
recipes  
Professor  
libraries used and authors  
additional inspiration on how to layout a github project from:
