'use strict';

const activity = require('../bin/index.js');

describe('Activity', () => {
	it('.getLastInputTime() should return number', () => {
		expect(typeof activity.getLastInputTime()).toBe('number');
		expect(activity.getLastInputTime()).toMatch(/\d{1,}/);
	});

	it('.getCurrentKeyboardLanguage() should return current language', () => {
		const language = activity.getCurrentKeyboardLanguage();
    expect(typeof language).toBe('string');
    expect(language.length).toBeGreaterThan(0);
	});
});
