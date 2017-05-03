#!/usr/bin/env python
# -*- coding: UTF-8 -*-
doc_class = '\documentclass [landscape,8pt,a4paper,twocolumn]{article}'

head = '''\\title {NCTU\\_Yggdarsill Codebook}
\\usepackage{parskip}
\\usepackage{xeCJK} 
\\setCJKmainfont{SourceHanSerifTW-Light}
\\setmonofont{Courier New}
\\usepackage {listings}
\\usepackage {color}
\\usepackage [left=1.0cm, right=1.0cm, top=2.0cm, bottom=0.5cm]{geometry}
\\definecolor {mygreen}{rgb}{0,0.6,0}
\\definecolor {mygray}{rgb}{0.5,0.5,0.5}
\\definecolor {mymauve}{rgb}{0.58,0,0.82}
\\usepackage{fancyheadings}
\\rhead{\\thepage}
\\chead{初始化了嗎？陣列大小對嗎？\\texttt{x, y}沒寫反吧？會爆\\texttt{int}嗎？好，傳囉！}
\\lhead{NCTU\\_Yggdarsill}
\\pagestyle{fancy}
\\cfoot{}
\\setlength{\\headsep}{5pt}
\\setlength{\\textheight}{540pt}
'''

lstset = '''\\lstset {
  backgroundcolor=\\color{white},
  basicstyle=\\footnotesize\\ttfamily,
  breakatwhitespace=false,
  breaklines=true,
  captionpos=b,
  commentstyle=\\color{mygreen},
  deletekeywords={...},
  escapeinside={\\%*}{*)},
  extendedchars=true,
  frame=single,
  keepspaces=true,
  keywordstyle=\\color{blue},
  language=Octave,
  morekeywords={*,...},
  numbers=left,
  numbersep=4pt,
  numberstyle=\\scriptsize\\ttfamily\\color{mygray},
  rulecolor=\\color{black},
  showspaces=false,
  showstringspaces=false,
  showtabs=false,
  stepnumber=1,
  stringstyle=\\color{mymauve},
  tabsize=2,
  xleftmargin=15pt,
  framexleftmargin=15pt,
  framexrightmargin=0pt,
  framexbottommargin=0pt,
  framextopmargin=0pt,
}
'''

doc_head = '''\\begin {document}
\\thispagestyle{fancy}
{ \\Huge NCTU\\_Yggdarsill}
\\tableofcontents
'''

tail = '''
\\end{document}
'''

src_types = ['.c', '.cpp', '.java', '.py', '.sublime-build', '.sublime-settings']

lang_list = {
  '.c': 'c',
  '.cpp': 'c++',
  '.java': 'java',
  '.py': 'python',
  '.sublime-build': 'bash',
  '.sublime-settings': 'bash'
}

import os
import sys

def escape(s):
  spe = '#$%&_{}'
  for c in spe:
    s = s.replace(c, '\\'+c)
  return s

def capitalize(line):
    return ' '.join(s[0].upper() + s[1:] for s in line.split(' '))

outname = 'codebook.tex'
sys.stdout = open(outname, 'w')
print doc_class
print head
print lstset
print doc_head
for root, dirs, files in os.walk('.'):
  if root.find('.svn') >= 0:
    continue
  secname = os.path.basename(root)
  if secname.startswith('.'):
    continue
  if escape(secname) == 'code':
    continue
  print '\\section{' + capitalize(secname.replace('_', ' ')) + '}'
  for name in files:
    base, ext = os.path.splitext(name)
    if name != 'vimrc' and ext not in src_types:
      continue
    print '\\subsection{' + capitalize(base.replace('_', ' ')) + '}'
    if ext not in src_types:
      lang = 'bash'
    else:
      lang = lang_list[ext]
    print '\\lstinputlisting [language=' + lang + '] {\"code/' + escape(secname) + '/' + name + '\"}'
print tail
sys.stdout.flush()
# subprocess.call(['bg5pdflatex', outname])
