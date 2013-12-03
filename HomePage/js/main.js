function shiftColor(id,color)
{
	document.getElementById(id).style["color"] = color;
}

function highLight(obj,color)
{
	obj.style["color"] = color;
}

function setSize(id)
{
	obj = document.getElementById(id);
	var bHeight = obj.contentWindow.document.body.scrollHeight;
	var dHeight = obj.contentWindow.document.documentElement.scrollHeight;
	var height = Math.max(bHeight, dHeight);
	obj.height =  height;

	var bWidth = obj.contentWindow.document.body.scrollWidth;
	var dWidth = obj.contentWindow.document.documentElement.scrollWidth;
	var width = Math.max(bWidth,bWidth);
	width = Math.max(width,850);
	obj.width = width;
}

