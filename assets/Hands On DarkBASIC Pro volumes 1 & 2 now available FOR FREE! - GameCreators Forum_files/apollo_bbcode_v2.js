/*
	----------------------------------------------------------------------------------------
	Apollo BBCode Function Set - Version 2.0 - June 7th 2006
	----------------------------------------------------------------------------------------

	By Richard Davey (rich@thegamecreators.com)

	These scripts have been tested and confirmed working in:
	
	Firefox 1.5.0.4 (Windows)
	Firefox 1.5.0.3 (OS X)
	IE 6 (Windows)
	Opera 8 (Windows)
	Safari 2.0.3 (OS X)
	
	They failed in OmniWeb 5, so I guess that rules out any WebKit based browser
*/

//	Our Globals

//	Change this to the ID of the textarea which collects the form data
var textarea_id = 'msgBody';

//	Internal global arrays, do not change
var tags = new Array();
var tags_holder = new Array();

/*
	----------------------------------------------------------------------------------------
	getSelected()
	----------------------------------------------------------------------------------------

	This function will return whatever text the user has selected in the current page.
	It takes into consideration a specified textarea first, then the document itself.

	Arguments:
	
	strict (boolean) = 'true' means we only check the textarea, 'false' checks whole document
*/

function getSelected(strict)
{
	var textarea = document.getElementById(textarea_id);
	var txt = new String('');
	var txt_unset = true;

	//	IE can select from anywhere in the document (including textarea) with just this:
	if (typeof(document.selection) != 'undefined' && typeof(textarea.setSelectionRange) == 'undefined')
	{
		//	If we're in strict mode, check where this selection occured
		if (strict)
		{
			//	We want text types only (avoid images / binary ranges)
			if (document.selection.type == 'Text')
			{
				//	Get the selected text and create a range from it
				selected = document.selection.createRange();

				//	Was the selected text within the textarea element ID?
				if (selected.parentElement().id == textarea_id)
				{
					txt = selected.text;
					txt_unset = false;
				}
			}
		}
		else
		{
			//	We want text types only (avoid images / binary ranges)
			if (document.selection.type == 'Text')
			{
				txt = document.selection.createRange().text;
				txt_unset = false;
			}
		}
	}

	//	Gecko needs to check within the textarea first
	if (textarea.setSelectionRange && txt_unset)
	{
		//	Check our textarea
		if (textarea.value.substring(textarea.selectionStart, textarea.selectionEnd) !== '')
		{
			txt = textarea.value.substring(textarea.selectionStart, textarea.selectionEnd);
			txt_unset = false;
		}
	}

	//	If we can check the whole document, then do so ...
	if (strict == false)
	{
		//	Nothing in the textarea selected? Then check the window
		if (window.getSelection && txt_unset)
		{
			if (window.getSelection() !== '')
			{
				txt = window.getSelection();
				txt_unset = false;
			}
		}
	
		//	Finally check the rest of the document (deprecated function, but Opera 8 needs it)
		if (document.getSelection && txt_unset)
		{
			if (document.getSelection() !== '')
			{
				txt = document.getSelection();
				txt_unset = false;
			}
		}
	
	}

	//	Return the text that was selected, if any
	return txt;
}

/*
	----------------------------------------------------------------------------------------
	injectText
	----------------------------------------------------------------------------------------
	
	This function will wrap the given text around the currently selected text within the 
	textarea. If no text is selected the text is appended onto the end of the textarea.
	
	Arguments:

	text (string) = the text to be inserted into the textarea
*/

function injectText(text)
{
    var txtarea = document.getElementById(textarea_id);

    var scrollPos = txtarea.scrollTop;
    var strPos = 0;
    var br = ((txtarea.selectionStart || txtarea.selectionStart == '0') ? 
    "ff" : (document.selection ? "ie" : false ) );
    if (br == "ie") { 
        txtarea.focus();
        var range = document.selection.createRange();
        range.moveStart ('character', -txtarea.value.length);
        strPos = range.text.length;
    }
    else if (br == "ff") strPos = txtarea.selectionStart;
    
    var front = (txtarea.value).substring(0,strPos); 
    
    if(selectionInsideTextarea()==''){
      var back = (txtarea.value).substring(strPos,txtarea.value.length);  
    } else {
      var selectedText = selectionInsideTextarea();
      var offset = selectedText.length;
      var back = (txtarea.value).substring(strPos+offset,txtarea.value.length);
    }
    
    txtarea.value=front+text+back;
    strPos = strPos + text.length;
    if (br == "ie") { 
        txtarea.focus();
        var range = document.selection.createRange();
        range.moveStart ('character', -txtarea.value.length);
        range.moveStart ('character', strPos);
        range.moveEnd ('character', 0);
        range.select();
    }
    else if (br == "ff") {
        txtarea.selectionStart = strPos;
        txtarea.selectionEnd = strPos;
        txtarea.focus();
    }
    txtarea.scrollTop = scrollPos;
}

function selectionInsideTextarea(){
  var textComponent = document.getElementById(textarea_id);

  var selectedText;
  selectedText = '';
  // IE version
  if (document.selection != undefined)
  {
    textComponent.focus();
    var sel = document.selection.createRange();
    selectedText = sel.text;
  }
  // Mozilla version
  else if (textComponent.selectionStart != undefined)
  {
    var startPos = textComponent.selectionStart;
    var endPos = textComponent.selectionEnd;
    selectedText = textComponent.value.substring(startPos, endPos)
  }
  return selectedText;
}

function selectText(containerid) {
    if (document.selection) {
        var range = document.body.createTextRange();
        range.moveToElementText(document.getElementById(containerid));
        range.select();
    } else if (window.getSelection) {
        var range = document.createRange();
        range.selectNode(document.getElementById(containerid));
        window.getSelection().addRange(range);
    }
}

/*
	----------------------------------------------------------------------------------------
	singleTagHandler()
	----------------------------------------------------------------------------------------
	
	When you don't select any text this will add an 'open' tag. When you next click the tag
	button it will close the tag.
	
	Set the 'allow_nesting' var (boolean) to true or false to control if nested tags are
	allowed. For example if the user had entered:
	
	[b][u]atari
	
	With allow_nesting ON (true) if the user was to click the 'b' tag it would insert a [/b]
	closing the previous bold tag, even though it is incorrect mark-up (the u should be closed first)
	
	With allow_nesting OFF (false) it would insert a new [b] tag, because in order to keep
	the nesting correct the user should have clicked the 'u' tag first (to close the currently
	open underscore tag) and then 'b'.
	
	Arguments:
	
	tag (string) - The tag in question, can be any valid string that works as an array key
	tag_open (string) - How the open tag should be formed
	tag_close (string) - How the close tag should be formed

*/

function singleTagHandler(tag, tag_open, tag_close)
{
	//	Will you allow them to nest invalid tags, or do they have to close previous ones first?
	var allow_nesting = true;

	if (allow_nesting)
	{
		//	If invalid tag nesting is allowed, we just need to keep track of single tag types
		if (tags_holder[tag] == tag_open)
		{
			tags_holder[tag] = tag_close;
			injectText(tag_close);
		}
		else
		{
			tags_holder[tag] = tag_open;
			injectText(tag_open);
		}
	}
	else
	{
		//	Check the most recent tag in the array, if match then close and go
		len = tags.length - 1;
		
		if (tags[len] == tag)
		{
			//	We found an open matching tag, so close it
			injectText(tag_close);
			tags.pop();
		}
		else
		{
			//	Nothing matched, so open a new tag
			injectText(tag_open);
			tags.push(tag);
		}
	}
}

/*
	----------------------------------------------------------------------------------------
	insertTag()
	----------------------------------------------------------------------------------------
	
	A generic function that takes the tag parameter and wraps that around the selected text.
	
	If no text is selected it will start an open tag.
	
	The scope controls where the tag text can be selected from (false = anywhere)

	Arguments:
	
	tag (string) - the tag to be inserted
	scope (boolean) - true allows the text to be selected from anywhere in the document,
	                  false limits it to just the textarea
	
*/

function insertSmiley(tag)
{
    text = tag + selected;
    injectText(text);
}

function insertSingleTag(tag, scope)
{
	var selected = new String(getSelected(scope));
	
	var tag_open = '[' + tag + ']';
	
	//	Anything selected?
	
	if (selected.length > 0)
	{
		//	Yes, so wrap the text and go
		text = tag_open + selected;
		injectText(text);
	}
	else
	{
		//	No, so open the tag, append and record
		singleTagHandler(tag, tag_open, '');
	}
}

function insertTag(tag, scope)
{
	var selected = new String(getSelected(scope));
	
  if(tag=="quote"){
    var tag_open = '[' + tag + '=]';  
  } else {
    var tag_open = '[' + tag + ']';
  }
	var tag_close = '[/' + tag + ']';
	
	//	Anything selected?
	
	if (selected.length > 0)
	{
		//	Yes, so wrap the text and go
		text = tag_open + selected + tag_close;
		injectText(text);
	}
	else
	{
		//	No, so open the tag, append and record
		singleTagHandler(tag, tag_open, tag_close);
	}
}

function insertAdvanceTag(tag, attrib, scope)
{
	var selected = new String(getSelected(scope));
	
  if(attrib==""){
    var tag_open = '[' + tag + ']';  
  } else {
    var tag_open = '[' + tag + '=' + attrib + ']';
  }
	var tag_close = '[/' + tag + ']';
	
	//	Anything selected?
	
	if (selected.length > 0)
	{
		//	Yes, so wrap the text and go
		text = tag_open + selected + tag_close;
		injectText(text);
	}
	else
	{
		//	No, so open the tag, append and record
		singleTagHandler(tag, tag_open, tag_close);
	}
}

function insertColorTag(tag, scope)
{
	var selected = new String(getSelected(scope));
	
	var tag_open = '[' + tag + ']';
	var tag_close = '[/color]';
	
	//	Anything selected?
	
	if (selected.length > 0)
	{
		//	Yes, so wrap the text and go
		text = tag_open + selected + tag_close;
		injectText(text);
	}
	else
	{
		//	No, so open the tag, append and record
		singleTagHandler(tag, tag_open, tag_close);
	}
}

function insertCodeTag(tag, attrib, scope)
{
	var selected = new String(getSelected(scope));
	
	var tag_open = '[' + tag + ' lang='+ attrib +']';
	var tag_close = '[/code]';
	
	//	Anything selected?
	
	if (selected.length > 0)
	{
		//	Yes, so wrap the text and go
		text = tag_open + selected + tag_close;
		injectText(text);
	}
	else
	{
		//	No, so open the tag, append and record
		singleTagHandler(tag, tag_open, tag_close);
	}
}

/*
	----------------------------------------------------------------------------------------
	insertSmiley()
	----------------------------------------------------------------------------------------
	
	A small wrapper function to the injectText() function for smiley faces and icons
	
	Arguments:
	
	smiley (string) - the smiley face (or icon) text to insert into the textarea

*/

function insertSmiley(smiley)
{
	injectText(smiley);
}

/*
	----------------------------------------------------------------------------------------
	insertLink()
	----------------------------------------------------------------------------------------
	
	This will insert an HTTP link into the textarea. You can select any text on the page
	(or within the textarea) and it will then prompt you to enter the URL, turning that
	text into a link to the given URL.
	
	If the selected text starts with http:// or www then it won't prompt you to enter the
	URL, it will just use what you've selected automatically. Way cool! :)
	
	If you've selected nothing, it'll prompt for a URL.
	
*/

function insertLink()
{
	//	Text for hyper-links can be selected from anywhere on the page
	var selected = new String(getSelected(false));

	if (selected.length > 0)
	{
		//	If the selected text starts with http:// then don't ask for the URL, use that
		if (selected.substring(0, 7) == 'http://')
		{
		    var href = "[href=" + selected + "]" + selected + "[/href]";
		}
		else if (selected.substring(0, 3) == 'www')
		{
		    var href = "[href=http://" + selected + "]" + selected + "[/href]";
		}
		else
		{
		    var url = prompt("Please enter the url", "http://");
		    var href = "[href=" + url + "]" + selected + "[/href]";
		}
	}
	else
	{
	    var url = prompt("Please enter the url", "http://");
	    var href = "[href]" + url + "[/href]";
	}

	injectText(href);
}

/*
	----------------------------------------------------------------------------------------
	insertImage()
	----------------------------------------------------------------------------------------
	
	Allows the user to insert a link to an image hosted remotely. It will check the last few
	characters of the selected text and if they matcha valid browser image (gif, jpeg, png)
	it will automatically create the link, otherwise it will prompt the for URL. The text can
	be anywhere in the document or textarea.

	If you've selected nothing, it'll prompt for a URL.
	
*/

function insertImage()
{
	//	Selecting a link to an image converts it to a link automatically
	var selected = new String(getSelected(false));

	if (selected.length > 0)
	{
		var location = selected.toLowerCase();

		//	If the selected text ends with a valid image format, convert it
		if (location.substr(-3,3) == 'gif' || 
			location.substr(-3,3) == 'jpg' || 
			location.substr(-4,4) == 'jpeg' || 
			location.substr(-3,3) == 'png' ||
			location.substr(0,45) == 'https://forum.thegamecreators.com/attachment/'
			)
		{
		    var href = "[img]" + selected + "[/img]";
		}
		else
		{
		    var url = prompt("Please enter the url of the image", "http://");
		    var href = "[img]" + url + "[/img]";
		}
	}
	else
	{
		var url = prompt("Please enter the url of the image", "http://");
		var href = "[img]" + url + "[/img]";
	}

	injectText(href);
}

/*
	----------------------------------------------------------------------------------------
	smileyList()
	----------------------------------------------------------------------------------------
	
	Opens a window showing the other smiley faces and icons on offer
	
*/

function smileyList()
{
	window.open('xt/smilies.php','Smilies','width=170,height=500,resizable=no,scrollbars=yes'); 
}

/*
	----------------------------------------------------------------------------------------
	expandIt()
	----------------------------------------------------------------------------------------
	
	Expands in-line code blocks
	
	Arguments:
	
	objId (object) - Object ID of the code to expand/collapse
	
*/

function expandIt(objId) 
{
	code = document.getElementById(objId);
	code.style.display = (code.style.display == "none" ) ? "" : "none";
}

var viewportwidth = -1;
var viewportheight = -1;

function calculateViewportSize()
{ 
    if (typeof window.innerWidth != 'undefined')
    {
        // the more standards compliant browsers (mozilla/netscape/opera/IE7) use window.innerWidth and window.innerHeight
        viewportwidth = window.innerWidth;
        viewportheight = window.innerHeight;
    }
    else if (typeof document.documentElement != 'undefined' 
          && typeof document.documentElement.clientWidth != 'undefined' 
          && document.documentElement.clientWidth != 0)
    {
        // IE6 in standards compliant mode (i.e. with a valid doctype as the first line in the document)
        viewportwidth = document.documentElement.clientWidth;
        viewportheight = document.documentElement.clientHeight;
    }
    else
    {
        // older versions of IE
        viewportwidth = document.getElementsByTagName('body')[0].clientWidth,
        viewportheight = document.getElementsByTagName('body')[0].clientHeight
    }
}

function getViewportWidth()
{
    calculateViewportSize();
    return viewportwidth;
}

function getViewportHeight()
{
    calculateViewportSize();
    return viewportheight;
}