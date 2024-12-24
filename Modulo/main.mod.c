#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe2208f4d, "single_open" },
	{ 0x3469b442, "filp_open" },
	{ 0x2e9b5a0f, "kernel_read" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x40c7247c, "si_meminfo" },
	{ 0xb869125d, "seq_printf" },
	{ 0xd817e20e, "filp_close" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xc29509a1, "remove_proc_entry" },
	{ 0xd7c2b04d, "seq_read" },
	{ 0xab380b4, "single_release" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x2a0a2332, "proc_create" },
	{ 0x122c3a7e, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe97223b3, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9D374831CDC61B4D2A53FBB");
