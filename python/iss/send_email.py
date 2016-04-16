#!/usr/bin/env python
#-*-coding:utf-8-*-
from email import encoders
from email.header import Header
from email.utils import parseaddr, formataddr
from email.mime.text import MIMEText
import smtplib
import urllib2

##CONFIG
server_smtp = 'smtp.sina.com'
server_smtpport = 25
sender_name = 'inksmallfrogsend'
sender_pass = '0printf();'

def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((Header(name, 'utf-8').encode(), \
                       addr.encode('utf-8') if isinstance(addr, unicode) else addr))

def send_email(to_addr, subject, message, msg_type):
    server = smtplib.SMTP(server_smtp, server_smtpport)
    server.login(sender_name, sender_pass)
    sender_addr = sender_name + "@sina.com"
    msg = MIMEText(message, msg_type, 'utf-8')
    msg['From'] = _format_addr(u'inksmallfrogsender <%s>' % sender_addr)
    msg['To'] = _format_addr(u'%s' % (";".join(to_addr)))
    msg['Subject'] = Header(subject, 'utf-8').encode()
    server.sendmail(sender_addr, to_addr, msg.as_string())
    server.quit()
    
