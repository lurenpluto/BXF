----------------------------
--//GetFileAbsPath API
----------------------------
function GetFileAbsPath(relativePath)
     local pos1, pos2 = string.find(__document, "BoltBrowserObject")
     local root = string.sub(__document, 1, pos2);
     return root..relativePath
end

----------------------------
--//MainWnd Create Event
----------------------------
function OnCreate(self)
	local objTree = self:GetBindUIObjectTree()
	local browser = objTree:GetUIObject("browser")

	--//Register a Lua function to browser
	browser:RegisterLuaFunction("testfunc",function(args)
		--//format the args sent from javascript
		local format = "-result-\ncity:%s\nstreet:%s\npostcode:%s"
		local info = string.format(format,args['city'],args['street'],args['postcode'])

		--//show args
		XLMessageBox(info)

		--//return result to javasctipt 
		return {["result"]="bolt"}
	end)
end

----------------------------
--//MainWnd Resize Event
----------------------------
function OnSize(self, sizetype, width, height)
	if type_ == "min" then
		return
	end

	--//resize the objecttree
	local objectTree = self:GetBindUIObjectTree()
	local rootObject = objectTree:GetRootObject()
	rootObject:SetObjPos(0, 0, width, height)
end

----------------------------
--//MainWnd Close Event
----------------------------
function OnClose(self)
	--//Call UELoader Global API to quit the app
	Quit()
end

----------------------------
--//browser object 
--//OnLoadingStateChange Event
----------------------------
function OnLoadingStateChange(self, isLoading, canGoBack, anGoForward)

end

----------------------------
--//browser object 
--//OnBeforeNavigation Event
----------------------------
function OnBeforeNavigation(self, frame, url, navigation_type, is_redirect)
	return 0, false, true, true
end

----------------------------
--//browser object 
--//OnBeforePopup Event
----------------------------
function OnBeforePopup(self, frame, targetUrl, targetFrameName)
	local childBrowser = self:GetParent():GetObject("childbrowser")
	childBrowser:Navigate(targetUrl)
end

----------------------------
--//browser object 
--//OnJavaScriptMessageReceived Event
----------------------------
function OnJavaScriptMessageReceived(self,messageName,args)
	--//format args sent from javascript
	local format = "message:%s\ncity:%s\nstreet:%s\npostcode:%s"
	local info = string.format(format,messageName,args['city'],args['street'],args['postcode'])
	
	--//show args
	XLMessageBox(info)

	--//call javasctipt function
	self:CallJavascriptFunction('alert',{["name"]="bolt"},function(ret)
		XLMessageBox(ret['name'])
	end)
end

----------------------------
--//CallJavascript
----------------------------
function CallJavascriptButton_MouseLeftDown(self)
	--//get browser object
	local objTree = self:GetOwner()
	local browser = objTree:GetUIObject("browser")

	--//call javascript function
	browser:CallJavascriptFunction('alert',{["name"]="bolt"},function(ret)
		XLMessageBox(ret['name'])
	end)
end

----------------------------
--//SendLuaMessage to Javascript
----------------------------
function SendLuaMessage2JavascriptButton_MouseLeftDown(self)
	--//get browser object
	local objTree = self:GetOwner()
	local browser = objTree:GetUIObject("browser")

	--//send message to javascript
	browser:SendMessage('lua_message',{["name"]="bolt message"})
end

