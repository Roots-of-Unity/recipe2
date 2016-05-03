
## recipe2 ##
a command line tool for recipes and shopping lists

#### Table of Contents ####
<!-- MarkdownTOC autolink=true depth=3 bracket=round -->

- [Overview](#overview)
- [Description of Problem](#description-of-problem)
- [Proposed Solution](#proposed-solution)
- [Shopping List Ordering Algorithm](#shopping-list-ordering-algorithm)
- [Example Toolchain Scenario](#example-toolchain-scenario)
- [Next Steps](#next-steps)
- [License](#license)
- [Credits and Thanks](#credits-and-thanks)
- [Contact](#contact)

<!-- /MarkdownTOC -->

#### Overview ####
Paper is still the king for shopping lists. I need to develop a computational solution that works with this fact.

A lot of details can be extracted by combining a recipe with other lists. The name of the program is meant to reflect this property (hypothetical examples, run the program recipe2 --help to see current features): recipe2 -shoppingList, recipe2 –nutritionInfo. These returned structures are lists as well and can be further utilized. 
#### Description of Problem ####
Have you ever gone out to the store and forgotten something on your shopping list due to bad organization? Do you frequently do the shopping for other people, and have to manage multiple shopping lists from multiple persons? Do you meal prep, and find that the thought of compiling the list into the order of the grocery store is annoying? If so, then recipe2 can help you! 
#### Proposed Solution ####
There's a better way to compile grocery lists, or rather there's a better way for all shopping lists in general: Use the Shopping List Ordering Algorithm (described in the next section). The SLOA works along with the idea that every retail store has an optimal path through the store, and that you, the shopper, have already subconsciously figured out this route. You just need to dump it from your mind and associate it with the items in the store.

In the future, this project might allow you to maintain your lists online, and utilize the "order" of a store (I'll refer to this as a schema from time to time in this document).

Every time you need to generate a list, recipe2 can read the schema of the store (... and eventually download a near perfect schema that others have collectively compiled on the Internet) and associate the order with the items you need to buy again on your list. Then, it prompts you for the potential location of unknown items on your shopping run! (feature not yet implemented)!

#### Shopping List Ordering Algorithm ####

Frustrated after missing an item while out buying groceries. I came up with a scheme to organize the handwritten lists.

Start with the first item on the list.  
Mark a letter A next to it.  
Move to the next item.  
Ask yourself: Does this item come before/after the other item on this list?   or is it near the other item?  
If it comes after item A. Mark it B  
If it comes before item A. Mark it with a smiley face or other arbitrary symbol that isn't in the alphabet.  
If it is near item A. Mark it with an A as well.  

This system has some shortcomings.
During the first few weeks of this assignment, I refined this process, and documented any other idea that popped into my head. They're all in this document and scanned in the journal in /documentation/journal.

Here's the thought process that leads to the refined system:  
I need an ordering system that allows for an arbitrary number of unknown items to be ordered at a later time.

I also need symbols that have a sequence that everyone agrees on. Oh how convenient. Let's switch from letters to decimals. Decimal numbers satisfy both needs.

I also need to be able to use multiple lists from different sources. The star symbol can be used for referencing other lists, just like it is in cpp.

So the new version goes like this:  
Start with the first (or wherever item) on the list.  
Mark it with your favorite number.  
Move to the next item.  
Ask yourself: Does this item come before/after another item on this list?
or is it near the other item?  
If it comes after the first item, mark it with a number that comes after you're selected number.  
If it comes before the first item, mark it with a number that comes before the first item. Negatives work too!
If it is near the first item. Mark it with the same number as that item!

Here's the best part:

If you mess up, and you don't see another obscure item on the list that is between say items marked with 101 cheese and 102 soda, then just mark it 101.5 and there you have it. Decimals can go forever like that!

There's one more annoyance. You need to sort the list in order. recipe2 as is, is able to do that for your most common recipes that you keep on the computer. Print off the recipe2 list. Then, you can take your handwritten lists, and whenever you see a insertion point on the generated list: like "hey!" This item belongs in between x and y on my recipe2 list, just mark in between with a star and then what list the other stuff is on, and reuse the same schema of order (in other words the numeric symbols you're using presently for that collection of lists).

In theory, I can store the "order" of a store to cross reference with future shopping lists. I'd know that eggs come before cheese. recipe2 does not have this implemented yet, but my work this session is required to get that feature working in the future.

I can the prompt the user, when a new item is added to a store schema, and question where the item belongs in relation to the other items. This is perhaps best done on a mobile device with a touch screen. Later sections expand on this more.

#### Example Toolchain Scenario ####
Example: I want to prepare a weeks' worth of freezer meals for my family. So I begin by generating a shopping list using [Gourmet Recipe Manager](https://github.com/thinkle/gourmet). I want to make one of every dish in my database and 2 slow cooker green bean sides:

![](http://i.imgur.com/vnxz9eB.png)

So I generate a shopping list:

![](http://i.imgur.com/H1CchIB.png)

and format it slightly and print it: (future developments might include using Gourmet Recipe Manager's sqlite database directly)

![](http://i.imgur.com/cy8Tnv1.jpg)

Now that the list is printed firmly onto the original computational device: paper; I can proceed and order it according to the Shopping List Ordering Algorithm described in detail in the self-named section.
![](http://i.imgur.com/t9PFZVz.jpg)

Now, while that list is now "ordered" (future developments include a mobile app to perform this ordering. It's easier graphically and with touch.) in the sense that I've extracted the information that my head knows about 86th Street Costco inventory sequence, it won't be helping anyone in its present form. The list needs to be organized from least to greatest according to the penciled in sequence numbers.

To do that, (and this is why a graphically and touch based app would be the best interface here) I'm going to turn that boring task over to my program. But first, I need to prepare a file that can be read by my project.

I quickly copy and paste the list I printed out into a column in a spreadsheet.

![](http://i.imgur.com/Lv02fYZ.png)

Then I visually parse the hand-sequenced shopping list into the spreadsheet. This is easy because the items are in the same order in both paper and spreadsheet.

![](http://i.imgur.com/c65fG5j.png)

Now, the magic can happen! Observers may note that You can sort the spreadsheet and generate an ordered list, however, it would be challenging to store an overall "schema" about a particular shopping-store using this method. My project takes the first steps into fully implementing store  sequence schemas.

Next, export the spreadsheet as an UTF-8 encoded, comma separated values file (*.csv):

![](http://i.imgur.com/joN7CSD.png)

For added compatibility (un-necessary on the system I tested with): Use a full-featured text editor (like Notepad++ on Windows) to make sure that the file is UTF-8 without BOM (That's byte order mark. It denotes which UTF encoding the file is in. There are several UTF encodings. The BOM could potentially cause issues.) And make sure that the line ending EOL character matches the target system. I tested with both and the project ran fine.

Next, put your single or multiple shopping list files... (that are ordered as a single sequence. For example: multiple sequences through a store would be lists you made for different trips to the store on different days. Taken together, these lists would not be a single sequence. Ordering these into one schema about a store: say 86th Street Costco is where I have an algorithm developed: see the Shopping List Ordering Algorithm section, and will be implemented in later sessions. The part I coded for this session will be necessary to implement this further down the road.) 

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
- Finish unimplemented features described in problems section.
- Implement a "spacing" function to spread out the decimal numbers to larger whole numbers. This way you don't get things like 101.9993. This gets mapped to say 5000 (the only thing that matters is sequence, face value is irrelevant.)
- GUI Auto Shopper App: It collaboratively maintains a giant database of store item schemas. This is how I'd start monetizing. When I actually became a company, I'd use my purchasing power to snuggle up with retailers for their actual parsable catalog, and make more money datamining.
  - For now, the grocery shopping app is a PnP (pen and paper... the original computation device) application
- CLI "Store the Store" Schema Component: Assumes correct ordering of a store. The correctness will be determined by users via some algorithm. This is what I have partially implemented. This will go onto be a backend to the different facets of the project.
- A smartphone/GUI/custom hardware component that uses OCR to read receipts after a shopping run to see what you actually acquired and from what store. This is one way to weed out inaccurate data and unknown items in stores.
- Patent on an "ordering system that allows for an arbitrary number of unknown items to be ordered at a later time." Woops. There goes that one.
- Add a sharing component of lists for recipes and life in general.
- A GUI/smartphone/touch "editor" for managing stores and their items. Example UI drawings:  

For touch/mobile
![](http://i.imgur.com/OuSbsIx.jpg)

For tablet/desktop_browser
![](http://i.imgur.com/iIfRaAj.jpg)

- Alternate Names:
  - Shopping Tool
  - List Tool
  - Catalog Tool
  - Personal Purchasing Tool: The Future is Promising (R)
  - Buy Me This
  - AutoShopper
  - Jeeves
  - ListManager Pro - Ha! the name of this one makes me think of TradeSkillMaster on World of Warcraft or the spreadsheets of Eve: Online.
  - Never Forget Another Item on a List!

## License ##

<a href="http://www.opensource.org/"><img height="100" align="right" src="http://wiki.opensource.org/bin/download/OSI+Operations/Marketing+%26+Promotional+Collateral/OSI_certified_logo_vector.svg"></a>

recipe2 is certified [Open Source](http://www.opensource.org/docs/definition.html) software. It may be used for any purpose, including commercial purposes, at absolutely no cost. It is distributed under the terms of the [MIT license](http://www.opensource.org/licenses/mit-license.html) reproduced here.

> Copyright (c) 2016 Jace Thompson
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This site and software is not affiliated with or endorsed by the Open Source Initiative. For questions and suggestions about the recipe2 please contact the author at [jthompson161@ivytech.edu](mailto:jthompson161@ivytech.edu)

## Credits and Thanks ##
Dr. Diana Nixon - my CSCI 102 professor at Ivy Tech Community College - for the awesome semester, and for teaching us C++11 so well.  

My classmates this semester:

- Yoosuk
- Ben
- Xuyang
- Kevin
- Jay
- Bard
- Janna

Sample Recipes in *.txt form found [here](https://gist.github.com/Roots-of-Unity/5fbed865347c9366f61433f9fbdad6c0). As Gourmet XML file [here](https://gist.github.com/Roots-of-Unity/0c429ae012ace8e527112c9b7e2f3d9a). I give them my seal of approval. 

Software of Note:

- [Gourmet Recipe Manager](https://github.com/thinkle/gourmet) by Thomas Hinkle. I used this in the examples above. 

Playlists:  

- Battlestar Galactica Season 4 Soundtrack: [link](https://youtu.be/NY3gY48pxjA?list=PL95092E55EDA7E10D)  
  - Lots of coding was done to track 1 performed by Alessandro Juliani.
    - Composed by Bear McCreary
- The Martian OST: [link](https://youtu.be/W4u8-dS7Etg?list=PLFyzg2g9ronE9z6WTG-vq3sYXFeJzSz3_) 
  - by Harry Gregson-Williams
 

Library Credits:  
*Licenses are located in libraries directory of this project.*
 
I made use of:  

- [cxxopts](https://github.com/jarro2783/cxxopts) by Jarryd Beck for parsing command line arguments.
- [UTF8-CPP](https://github.com/nemtrif/utfcpp) by Nemanja Trifunovic for validating UTF-8.

Inspiration on how to layout a README.md from these immaculate projects:  
- [https://github.com/homebysix/recipe-robot](https://github.com/homebysix/recipe-robot)  
- [https://github.com/ColinH/PEGTL](https://github.com/ColinH/PEGTL)

## Contact ##
Jace Thompson  
[jthompson161@ivytech.edu](mailto:jthompson161@ivytech.edu)
