import sublime, sublime_plugin
import os

class print_file(sublime_plugin.TextCommand):
	def run(self, edit):
		os.system('cat -n "%s" > tmp.print; lpr tmp.print' % self.view.file_name())
		self.view.show_popup("JIZZ!!")
