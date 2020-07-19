namespace WindowsFormsApplication1
{
    partial class Level2EventResourceMatch
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Level2EventResourceMatch));
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(361, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(219, 20);
            this.label1.TabIndex = 51;
            this.label1.Text = "事件-资源时间关联匹配";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(48, 111);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(50, 49);
            this.label3.TabIndex = 57;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.ForeColor = System.Drawing.Color.DodgerBlue;
            this.label2.Location = new System.Drawing.Point(38, 320);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(489, 20);
            this.label2.TabIndex = 58;
            this.label2.Text = "|----------------事件发生时间------------------|";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(46, 56);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(949, 20);
            this.label4.TabIndex = 59;
            this.label4.Text = "|--------------------------------------数据资源有效时间----------------------------------" +
    "----|";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(383, 111);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(50, 49);
            this.label5.TabIndex = 60;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(138, 111);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(176, 34);
            this.label6.TabIndex = 61;
            // 
            // label7
            // 
            this.label7.Image = ((System.Drawing.Image)(resources.GetObject("label7.Image")));
            this.label7.Location = new System.Drawing.Point(48, 224);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(468, 34);
            this.label7.TabIndex = 62;
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(484, 118);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(176, 34);
            this.label8.TabIndex = 63;
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(714, 111);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(50, 49);
            this.label9.TabIndex = 64;
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(818, 126);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(176, 34);
            this.label10.TabIndex = 65;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("黑体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label11.Location = new System.Drawing.Point(585, 255);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(0, 20);
            this.label11.TabIndex = 66;
            // 
            // Level2EventResourceMatch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1006, 368);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Location = new System.Drawing.Point(200, 20);
            this.Name = "Level2EventResourceMatch";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "事件-资源时间关联匹配";
            this.TopMost = true;
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Level2EventResourceMatch_FormClosed);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Level2EventResourceMatch_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
    }
}