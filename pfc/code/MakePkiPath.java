import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;
import java.security.cert.X509Certificate;
import java.security.cert.CertificateFactory;
import java.security.cert.CertPath;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.BufferedInputStream;

public class MakePkiPath
{
    private static void display (String str)
    {
        System.out.println (str);
    }

    public static void main (String [] args) throws Exception
    {

        if (args.length < 1)
        {
            display ("Usage:: java MakePkiPath <certfile>");
            System.exit (1);
        }

        CertificateFactory cf = CertificateFactory.getInstance ("X.509");
        List certs = new ArrayList ();

        for (int i = 0; i < args.length; i++)
        {
            FileInputStream fis = new FileInputStream (args [i]);
            BufferedInputStream bis = new BufferedInputStream (fis);

            while (bis.available () > 0)
            {
                certs.add (cf.generateCertificate (bis));
            }
        }

        CertPath cp = cf.generateCertPath (certs);

        // print each certificate in the path
        Iterator i = cp.getCertificates ().iterator ();
        while (i.hasNext ())
        {
            X509Certificate cert = (X509Certificate) i.next ();
            display (cert.toString ());
        }

        display ("Creatint PkiPath");
        FileOutputStream fos = new FileOutputStream ("certs.pki");
        fos.write (cp.getEncoded ("PkiPath"));
        fos.close ();
    }
}

