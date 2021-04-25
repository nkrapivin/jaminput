-- hugs.lua

-- preload jaminput if it wasn't loaded.
if not jam then
	jam = require("jaminput")
end

function inputtest()
	-- print("INPUT_KEYBOARD=",INPUT_KEYBOARD)
	local inputs = {}

	-- симулирует нажатие Win-R (не забывайте что в Lua массивы с 1)
	inputs[1] = {}
	inputs[1].type = INPUT_KEYBOARD
	inputs[1].wVk = 0x5B -- VK_LWIN

	inputs[2] = {}
	inputs[2].type = INPUT_KEYBOARD
	inputs[2].wVk = GML_ord("R")

	inputs[3] = {}
	inputs[3].type = INPUT_KEYBOARD
	inputs[3].wVk = GML_ord("R")
	inputs[3].dwFlags = KEYEVENTF_KEYUP

	inputs[4] = {}
	inputs[4].type = INPUT_KEYBOARD
	inputs[4].wVk = 0x5B
	inputs[4].dwFlags = KEYEVENTF_KEYUP

	-- code значит сколько событий ввода было успешно отправлено
	-- (обычно равно количеству событий)
	-- если там -1 то походу событий нет вообще.
	local code = jam.sendinput(inputs)
	print("code = ",code)
end

-- libLassebq specific stuff below:

local T_obj_libLassebq = { }

function T_obj_libLassebq.Step(_pSelf, _pOther)
	if GML_keyboard_check_released(vk_f2) == 1 then
		inputtest()
	end
end

return { obj_libLassebq=T_obj_libLassebq }