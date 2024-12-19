/**
 * SyntaxHighlighter
 * http://alexgorbatchev.com/SyntaxHighlighter
 *
 * SyntaxHighlighter is donationware. If you are using it, please donate.
 * http://alexgorbatchev.com/SyntaxHighlighter/donate.html
 *
 * @version
 * 3.0.83 (July 02 2010)
 *
 * @copyright
 * Copyright (C) 2004-2010 Alex Gorbatchev.
 *
 * @license
 * Dual licensed under the MIT and GPL licenses.
 */
;(function()
{
    // CommonJS
    typeof(require) != 'undefined' ? SyntaxHighlighter = require('shCore').SyntaxHighlighter : null;

    function Brush()
    {
        var keywords =	'Function EndFunction For If EndIf Else Next Do loop Exit Global As Type EndType Gosub';

        var special =  'True False';

        this.regexList = [
            { regex: SyntaxHighlighter.regexLib.singleLineCComments,	css: 'comments' },			// one line comments
            { regex: SyntaxHighlighter.regexLib.multiLineCComments,		css: 'comments' },			// multiline comments
            { regex: new RegExp('^rem\\s.*$', 'gm'),		            css: 'comments' },          // rem comments
            { regex: new RegExp('^`\\s.*$', 'gm'),		                css: 'comments' },          // ` comments
            { regex: new RegExp(this.getKeywords(keywords), 'gmi'),		css: 'keyword' },			// keyword
            { regex: new RegExp(this.getKeywords(special), 'gmi'), 		css: 'color1' }
        ];
    };

    Brush.prototype	= new SyntaxHighlighter.Highlighter();
    Brush.aliases	= ['dbp'];

    SyntaxHighlighter.brushes.Dbp = Brush;

    // CommonJS
    typeof(exports) != 'undefined' ? exports.Brush = Brush : null;
})();
