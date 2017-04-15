'use strict'

const activity = require('../bin/index.js');

describe('Activity', () => {
	it('.getLastInputTime() should return number', () => {
		expect(activity.getLastInputTime()).toNotEqual(null);
		expect(activity.getLastInputTime()).toNotEqual(false);
		expect(activity.getLastInputTime()).toNotEqual(undefined);
		expect(activity.getLastInputTime()).toNotEqual({});
		expect(activity.getLastInputTime()).toNotEqual('');
		expect(activity.getLastInputTime()).toNotEqual('213');
		expect(activity.getLastInputTime()).toNotEqual([]);
		expect(activity.getLastInputTime()).toMatch(/\d{1,}/);
	})
	
	it('.getCurrentKeyboardLanguge() should return current language', () => {
		
	})
})