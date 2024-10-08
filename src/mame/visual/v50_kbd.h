// license: BSD-3-Clause
// copyright-holders: Dirk Best
/***************************************************************************

    Visual 50 Keyboard

***************************************************************************/

#ifndef MAME_VISUAL_V50_KBD_H
#define MAME_VISUAL_V50_KBD_H

#pragma once

#include "cpu/mcs48/mcs48.h"
#include "sound/beep.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class v50_kbd_device : public device_t
{
public:
	// construction/destruction
	v50_kbd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	// callbacks
	auto txd_cb() { return m_txd_cb.bind(); }
	auto cts_cb() { return m_cts_cb.bind(); }

	// from host
	void rxd_w(int state);

protected:
	// device_t overrides
	virtual const tiny_rom_entry *device_rom_region() const override ATTR_COLD;
	virtual void device_add_mconfig(machine_config &config) override ATTR_COLD;
	virtual ioport_constructor device_input_ports() const override ATTR_COLD;
	virtual void device_start() override ATTR_COLD;
	virtual void device_reset() override ATTR_COLD;

private:
	required_device<i8048_device> m_mcu;
	required_device<beep_device> m_buzzer;
	required_ioport_array<16> m_keys;

	devcb_write_line m_txd_cb;
	devcb_write_line m_cts_cb;

	bool m_prog;
	uint8_t m_key_row;

	uint8_t p1_r();
	void p2_w(uint8_t data);
	void prog_w(int state);
};

// device type declaration
DECLARE_DEVICE_TYPE(V50_KBD, v50_kbd_device)

#endif // MAME_VISUAL_V50_KBD_H
