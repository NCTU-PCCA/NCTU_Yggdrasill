#!/usr/bin/env python
doc_class = '\documentclass [landscape,8pt,a4paper,twocolumn]{article}'

head = '''\\title {NCTU\\_Yggdarsill Codebook}
\\usepackage{parskip}
\\usepackage{xeCJK} 
\\setCJKmainfont{SourceHanSansTWHK-Normal}
\\setmonofont{Courier New}
\\usepackage {listings}
\\usepackage {color}
\\usepackage [left=1.0cm, right=1.0cm, top=2.0cm, bottom=0.5cm]{geometry}
\\definecolor {mygreen}{rgb}{0,0.6,0}
\\definecolor {mygray}{rgb}{0.5,0.5,0.5}
\\definecolor {mymauve}{rgb}{0.58,0,0.82}
\\usepackage{fancyheadings}
\\rhead{\\thepage}
\\lhead{National Chiao Tung University, NCTU\\_Yggdarsill}
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
{ \\Huge National Chiao Tung University \\\\ Team Reference Document}
\\tableofcontents
\\newpage
'''

tail = '''\\input{note.tex}
\\end{document}
'''

src_types = ['.c', '.cpp', '.java', '.py']

lang_list = {
  '.c': 'c',
  '.cpp': 'c++',
  '.java': 'java',
  '.py': 'python'
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
